/*
  ext_int.c - External interrupts handling
  Part of Grbl

  Copyright (c) 2021 FoxOne

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl.h"

// Meta2560 external interrupts map
// PD0 INT0	
// PD1 INT1	
// PD2 INT2	
// PD3 INT3	
// PE4 INT4	
// PE5 INT5	
// PE6 INT6	
// PE7 INT7	
// PB0 PCINT0
// PB1 PCINT1
// PB2 PCINT2
// PB3 PCINT3
// PB4 PCINT4
// PB5 PCINT5
// PB6 PCINT6
// PB7 PCINT7
// PE0 PCINT8
// PJ0 PCINT9
// PJ1 PCINT10
// PJ2 PCINT11
// PJ3 PCINT12
// PJ4 PCINT13
// PJ5 PCINT14
// PJ6 PCINT15
// PK0 PCINT16
// PK1 PCINT17
// PK2 PCINT18
// PK3 PCINT19
// PK4 PCINT20
// PK5 PCINT21
// PK6 PCINT22
// PK7 PCINT23

#define TRIGGER_MASK 0x03
#define HANDLER_MASK 0x70
#define USE_MASK     0x80

static uint8_t descr_table[4*8];

typedef void (*ISR_HADNLER)();

static ISR_HADNLER const handlers[] = {
  &system_control_isr,
  // something else ?
#ifndef DISABLE_HW_LIMITS
  &limits_isr,
#endif
};

#define READ_PCINT0_PIN PINB
#define READ_PCINT1_PIN (PINJ<<1) | (PINE & 1)
#define READ_PCINT2_PIN PINK

static uint8_t oldvalues[3];

void int_init()
{
  PCICR = 0;
  PCIFR = bit(PCIF0) | bit(PCIF1) | bit(PCIF2);
  PCMSK0 = 0;
  PCMSK1 = 0;
  PCMSK2 = 0;
  EIMSK = 0;
  EIFR = 0xff;	// bit(INTF0) | bit(INTF1) ...
  clear_vector( descr_table );
}

static int get_index_from_port_bit( char port, uint8_t bit )
{
  if ( bit<8 )	// just in case
  switch(port) {
	case 'B':
	  return 8+bit;
	case 'D':
	  if ( bit<4 ) return bit;
	  break;
	case 'E':
	  if ( bit>=4 ) return bit;
	  if ( bit==0 ) return 16;
	  break;
	case 'J':
	  if ( bit<7 ) return 17+bit;
	  break;
	case 'K':
	  return 24+bit;
  }
  return -1;
}

void int_enable( char port, uint8_t bit, uint8_t trigger, uint8_t handler )
{
  int idx;
  int tmp;

  idx = get_index_from_port_bit( port, bit );
  if ( idx<0 ) return;
  tmp = idx & 7;

  descr_table[idx] = trigger | (handler<<4) | USE_MASK;

  if ( idx>=24 ) {
	// PCINT2
	if ( PCMSK2==0 ) {
	  oldvalues[2] = READ_PCINT2_PIN;
	  PCICR |= bit(PCIE2);	// enable PCINT2
	}
	PCMSK2 |= bit(tmp);
  } else
  if ( idx>=16 ) {
	// PCINT1
    if ( PCMSK1==0 ) {
	  oldvalues[1] = READ_PCINT1_PIN;
	  PCICR |= bit(PCIE1);	// enable PCINT1
	}
	PCMSK1 |= bit(tmp);
  } else
  if ( idx>=8 ) {
	// PCINT0
	if ( PCMSK0==0 ) {
	  oldvalues[0] = READ_PCINT0_PIN;
	  PCICR |= bit(PCIE0);	// enable PCINT0
	}
	PCMSK0 |= bit(tmp);
  } else {
    // INT0-INT7
	tmp = (idx&3) << 1;	// shift
	if ( idx<4 )
	  EICRA = (EICRA & ~(TRIGGER_MASK << tmp)) | (trigger << tmp);
	else
      EICRB = (EICRB & ~(TRIGGER_MASK << tmp)) | (trigger << tmp);
	EIMSK |= bit(idx);	// enable INT<idx>
  }
}

void int_disable( char port, uint8_t bit )
{
  int idx;
  int tmp;

  idx = get_index_from_port_bit( port, bit );
  if ( idx<0 ) return;

  tmp = idx & 7;

  if ( idx>=24 ) {
	// PCINT2
	PCMSK2 &= ~bit(tmp);
	if ( PCMSK2==0 ) {
	  PCICR &= ~bit(PCIE2);	// disable PCINT2
	  PCIFR |= bit(PCIF2);	// clear interrupt flag
	}
  } else
  if ( idx>=16 ) {
	// PCINT1
	PCMSK1 &= ~bit(tmp);
    if ( PCMSK1==0 ) {
	  PCICR &= ~bit(PCIE1);	// disable PCINT1
	  PCIFR |= bit(PCIF1);	// clear interrupt flag
	}
  } else
  if ( idx>=8 ) {
	// PCINT0
	PCMSK0 &= ~bit(tmp);
	if ( PCMSK0==0 ) {
	  PCICR &= ~bit(PCIE0);	// disable PCINT0
	  PCIFR |= bit(PCIF0);	// clear interrupt flag
	}
  } else {
    // INT0-INT7
	EIMSK &= ~bit(tmp);	// disable INT<idx>
	EIFR = bit(tmp);	// clear interrupt flag
  }

  descr_table[idx] = 0;
}

static void pcint_isr( uint8_t *pold_value, uint8_t new_value, const uint8_t *descr )
{
  uint8_t changes, falling, rising;
  int idx;

  changes = new_value ^ *pold_value;
  falling = changes & *pold_value;
  rising = changes & new_value;
  *pold_value = new_value;
  uint8_t cond[] = { ~new_value, changes, falling, rising };
  // check 8 descriptors
  for( uint8_t mask=1; mask; mask<<=1 ) {
    uint8_t d = *descr++;
    if ( bit_istrue(d,USE_MASK) ) {
      // check condition
      if ( bit_istrue(cond[d&TRIGGER_MASK],mask) ) {
		idx = (d&HANDLER_MASK) >> 4;	// get handler index
		handlers[idx]();	// call isr handler
		// continue ?
	  }
	}
  }
}

static void int_isr( int i )
{
  int idx;
  // check USE_MASK ?
  idx = (descr_table[i]&HANDLER_MASK) >> 4;	// get handler index
  handlers[idx]();	// call isr handler
}

ISR(INT0_vect)
{
  int_isr(0);
}

ISR(INT1_vect)
{
  int_isr(1);
}

ISR(INT2_vect)
{
  int_isr(2);
}

ISR(INT3_vect)
{
  int_isr(3);
}

ISR(INT4_vect)
{
  int_isr(4);
}

ISR(INT5_vect)
{
  int_isr(5);
}

ISR(INT6_vect)
{
  int_isr(6);
}

ISR(INT7_vect)
{
  int_isr(7);
}

ISR(PCINT0_vect)
{
  pcint_isr( oldvalues+0, READ_PCINT0_PIN, descr_table+8 );
}

ISR(PCINT1_vect)
{
  pcint_isr( oldvalues+1, READ_PCINT1_PIN, descr_table+16 );
}

ISR(PCINT2_vect)
{
  pcint_isr( oldvalues+2, READ_PCINT2_PIN, descr_table+24 );
}
