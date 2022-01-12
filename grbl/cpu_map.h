/*
  cpu_map.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

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

/* The cpu_map.h files serve as a central pin mapping selection file for different 
   processor types or alternative pin layouts. This version of Grbl supports only the 
   Arduino Mega2560. */

#ifndef cpu_map_h
#define cpu_map_h

#include "nuts_bolts.h"

#define _CONCAT(x,y) x##y

#define DDR(port) _CONCAT(DDR,port)
#define PORT(port) _CONCAT(PORT,port)
#define PIN(port) _CONCAT(PIN,port)

#define STEP_MASK(i) bit(_CONCAT(STEP_B_,i))
#define STEP_DDR(i)  DDR(_CONCAT(STEP_P_,i))
#define STEP_PORT(i) PORT(_CONCAT(STEP_P_,i))
#define STEP_PIN(i)  PIN(_CONCAT(STEP_P_,i))

#define DIRECTION_MASK(i) bit(_CONCAT(DIRECTION_B_,i))
#define DIRECTION_DDR(i)  DDR(_CONCAT(DIRECTION_P_,i))
#define DIRECTION_PORT(i) PORT(_CONCAT(DIRECTION_P_,i))
#define DIRECTION_PIN(i)  PIN(_CONCAT(DIRECTION_P_,i))

#define STEPPER_DISABLE_MASK(i) bit(_CONCAT(STEPPER_DISABLE_B_,i))
#define STEPPER_DISABLE_DDR(i)  DDR(_CONCAT(STEPPER_DISABLE_P_,i))
#define STEPPER_DISABLE_PORT(i) PORT(_CONCAT(STEPPER_DISABLE_P_,i))
#define STEPPER_DISABLE_PIN(i)  PIN(_CONCAT(STEPPER_DISABLE_P_,i))

#define MIN_LIMIT_MASK(i) bit(_CONCAT(MIN_LIMIT_B_,i))
#define MIN_LIMIT_DDR(i)  DDR(_CONCAT(MIN_LIMIT_P_,i))
#define MIN_LIMIT_PORT(i) PORT(_CONCAT(MIN_LIMIT_P_,i))
#define MIN_LIMIT_PIN(i)  PIN(_CONCAT(MIN_LIMIT_P_,i))

#define MAX_LIMIT_MASK(i) bit(_CONCAT(MAX_LIMIT_B_,i))
#define MAX_LIMIT_DDR(i)  DDR(_CONCAT(MAX_LIMIT_P_,i))
#define MAX_LIMIT_PORT(i) PORT(_CONCAT(MAX_LIMIT_P_,i))
#define MAX_LIMIT_PIN(i)  PIN(_CONCAT(MAX_LIMIT_P_,i))

#define PROBE_MASK bit(PROBE_B)
#define PROBE_DDR  DDR(PROBE_P)
#define PROBE_PIN  PIN(PROBE_P)
#define PROBE_PORT PORT(PROBE_P)

#define SPINDLE_ENABLE_DDR      DDR(SPINDLE_ENABLE_P)
#define SPINDLE_ENABLE_PORT     PORT(SPINDLE_ENABLE_P)
#define SPINDLE_ENABLE_MASK     bit(SPINDLE_ENABLE_B)
#define SPINDLE_DIRECTION_DDR   DDR(SPINDLE_DIRECTION_P)
#define SPINDLE_DIRECTION_PORT  PORT(SPINDLE_DIRECTION_P)
#define SPINDLE_DIRECTION_MASK  bit(SPINDLE_DIRECTION_B)
#define SPINDLE_PWM_DDR		    DDR(SPINDLE_PWM_P)
#define SPINDLE_PWM_PORT        PORT(SPINDLE_PWM_P)
#define SPINDLE_PWM_MASK		bit(SPINDLE_PWM_B)

#define COOLANT_FLOOD_DDR   DDR(COOLANT_FLOOD_P)
#define COOLANT_FLOOD_PORT  PORT(COOLANT_FLOOD_P)
#define COOLANT_FLOOD_MASK  bit(COOLANT_FLOOD_B)
#define COOLANT_MIST_DDR    DDR(COOLANT_MIST_P)
#define COOLANT_MIST_PORT   PORT(COOLANT_MIST_P)
#define COOLANT_MIST_MASK   bit(COOLANT_MIST_B)

#define CONTROL_DDR       DDR(CONTROL_P)
#define CONTROL_PIN       PIN(CONTROL_P)
#define CONTROL_PORT      PORT(CONTROL_P)
#define CONTROL_MASK(n)   bit(CONTROL_B_##n)


#ifdef CPU_MAP_2560_INITIAL // (Arduino Mega 2560) Working @EliteEng

  // Serial port interrupt vectors
  #define SERIAL_RX USART0_RX_vect
  #define SERIAL_UDRE USART0_UDRE_vect

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
  #define STEP_P_0   A
  #define STEP_P_1   A
  #define STEP_P_2   A
  #define STEP_B_0   2 // MEGA2560 Digital Pin 24
  #define STEP_B_1   3 // MEGA2560 Digital Pin 25
  #define STEP_B_2   4 // MEGA2560 Digital Pin 26

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
  #define DIRECTION_P_0   C
  #define DIRECTION_P_1   C
  #define DIRECTION_P_2   C
  #define DIRECTION_B_0   7 // MEGA2560 Digital Pin 30
  #define DIRECTION_B_1   6 // MEGA2560 Digital Pin 31
  #define DIRECTION_B_2   5 // MEGA2560 Digital Pin 32

  // Define stepper driver enable/disable output pin.
  #define STEPPER_DISABLE_P_0  B
  #define STEPPER_DISABLE_P_1  B
  #define STEPPER_DISABLE_P_2  B
  #define STEPPER_DISABLE_B_0  7 // MEGA2560 Digital Pin 13
  #define STEPPER_DISABLE_B_1  7 // MEGA2560 Digital Pin 13
  #define STEPPER_DISABLE_B_2  7 // MEGA2560 Digital Pin 13

  // Define homing/hard limit switch input pins and limit interrupt vectors. 
  // NOTE: All limit bit pins must be on the same port
  #define MIN_LIMIT_P_0    B
  #define MIN_LIMIT_P_1    B
  #define MIN_LIMIT_P_2    B
  #define MIN_LIMIT_B_0    4 // MEGA2560 Digital Pin 10
  #define MIN_LIMIT_B_1    5 // MEGA2560 Digital Pin 11
  #define MIN_LIMIT_B_2    6 // MEGA2560 Digital Pin 12

  // just repeat
  #define MAX_LIMIT_P_0    B
  #define MAX_LIMIT_P_1    B
  #define MAX_LIMIT_P_2    B
  #define MAX_LIMIT_B_0    4 
  #define MAX_LIMIT_B_1    5 
  #define MAX_LIMIT_B_2    6 

// xmin PCINT4 PCINT0_vect PCMSK0/bit(4)
// ymin PCINT5 PCINT0_vect PCMSK0/bit(5)
// zmin PCINT6 PCINT0_vect PCMSK0/bit(6)
  #define LIMIT_INT_EN_BIT PCIE0  // Pin change interrupt enable bit
  #define LIMIT_INT_vect   PCINT0_vect 
  #define LIMIT_INT_PCMSK  PCMSK0 // Pin change interrupt register
  
  // Define spindle enable and spindle direction output pins.
  #define SPINDLE_ENABLE_P      H
  #define SPINDLE_ENABLE_B      3 // MEGA2560 Digital Pin 6
  #define SPINDLE_DIRECTION_P   E
  #define SPINDLE_DIRECTION_B   3 // MEGA2560 Digital Pin 5

  // Define spindle output pins.
  #define SPINDLE_PWM_P    H
  #define SPINDLE_PWM_B    4 // MEGA2560 Digital Pin 7

  // Define flood and mist coolant enable output pins.
  #define COOLANT_FLOOD_P   H
  #define COOLANT_FLOOD_B   5 // MEGA2560 Digital Pin 8
  #define COOLANT_MIST_P    H
  #define COOLANT_MIST_B    6 // MEGA2560 Digital Pin 9

  // Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
  #define CONTROL_P      K
  #define CONTROL_B_RESET         0  // MEGA2560 Analog Pin 8
  #define CONTROL_B_FEED_HOLD     1  // MEGA2560 Analog Pin 9
  #define CONTROL_B_CYCLE_START   2  // MEGA2560 Analog Pin 10
  #define CONTROL_B_SAFETY_DOOR   3  // MEGA2560 Analog Pin 11

// reset       PCINT16 PCINT2_vect PCMSK2/bit(0)
// feed_hold   PCINT17 PCINT2_vect PCMSK2/bit(1)
// cycle_start PCINT18 PCINT2_vect PCMSK2/bit(2)
// safety_door PCINT19 PCINT2_vect PCMSK2/bit(3)
  #define CONTROL_INT_EN_BIT PCIE2  // Pin change interrupt enable bit
  #define CONTROL_INT_vect   PCINT2_vect
  #define CONTROL_INT_PCMSK  PCMSK2 // Pin change interrupt register
  
  // Define probe switch input pin.
  #define PROBE_P        K
  #define PROBE_B        7  // MEGA2560 Analog Pin 15


  // Advanced Configuration Below You should not need to touch these variables
  // Set Timer up to use TIMER4B which is attached to Digital Pin 7
  #define SPINDLE_PWM_MAX_VALUE     1024.0 // Translates to about 1.9 kHz PWM frequency at 1/8 prescaler
  #ifndef SPINDLE_PWM_MIN_VALUE
    #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
  #endif
  #define SPINDLE_PWM_OFF_VALUE     0

  #define SPINDLE_TCCRA_REGISTER		TCCR4A
  #define SPINDLE_TCCRB_REGISTER		TCCR4B
  #define SPINDLE_OCR_REGISTER	  	OCR4B
  #define SPINDLE_COMB_BIT			    COM4B1

  // 1/8 Prescaler, 16-bit Fast PWM mode
  #define SPINDLE_TCCRA_INIT_MASK (bit(WGM40) | bit(WGM41))
  #define SPINDLE_TCCRB_INIT_MASK (bit(WGM42) | bit(WGM43) | bit(CS41)) 
  #define SPINDLE_OCRA_REGISTER   OCR4A // 16-bit Fast PWM mode requires top reset value stored here.
  #define SPINDLE_OCRA_TOP_VALUE  0x0400 // PWM counter reset value. Should be the same as PWM_MAX_VALUE in hex.

#endif

#ifdef CPU_MAP_2560_RAMPS_BOARD // (Arduino Mega 2560) with Ramps 1.4-1.6 Board

  // Serial port interrupt vectors
  #define SERIAL_RX USART0_RX_vect
  #define SERIAL_UDRE USART0_UDRE_vect
  
  // Define step pulse output pins.
  #define STEP_P_0 F	// X Step - Pin A0 (PF0)
  #define STEP_P_1 F // Y Step - Pin A6 (PF6)
  #define STEP_P_2 L // Z Step - Pin D46 (PL3)
  #define STEP_P_3 A // E0 Step - Pin D26 (PA4)
  #define STEP_P_4 C // E1 Step - Pin D36 (PC1)
//  #define STEP_P_5 
  #define STEP_B_0 0  // X Step - Pin A0 (PF0)
  #define STEP_B_1 6  // Y Step - Pin A6 (PF6)
  #define STEP_B_2 3  // Z Step - Pin D46 (PL3)
  #define STEP_B_3 4  // E0 Step - Pin D26 (PA4)
  #define STEP_B_4 1  // E1 Step - Pin D36 (PC1)
//  #define STEP_B_5 

  // Define step direction output pins.
  #define DIRECTION_P_0 F // X Dir - Pin A1 (PF1)
  #define DIRECTION_P_1 F // Y Dir - Pin A7 (PF7)
  #define DIRECTION_P_2 L // Z Dir - Pin D48 (PL1)
  #define DIRECTION_P_3 A // E0 Dir - Pin D28 (PA6)
  #define DIRECTION_P_4 C // E1 Dir - Pin D34 (PC3)
//  #define DIRECTION_P_5
  #define DIRECTION_B_0 1 // X Dir - Pin A1 (PF1)
  #define DIRECTION_B_1 7 // Y Dir - Pin A7 (PF7)
  #define DIRECTION_B_2 1 // Z Dir - Pin D48 (PL1)
  #define DIRECTION_B_3 6 // E0 Dir - Pin D28 (PA6)
  #define DIRECTION_B_4 3 // E1 Dir - Pin D34 (PC3)
//  #define DIRECTION_B_5

  // Define stepper driver enable/disable output pin.
  #define STEPPER_DISABLE_P_0 D // X Enable - Pin D38 (PD7)
  #define STEPPER_DISABLE_P_1 F // Y Enable - Pin A2 (PF2)
  #define STEPPER_DISABLE_P_2 K // Z Enable - Pin A8 (PK0)
  #define STEPPER_DISABLE_P_3 C // E0 Enable - Pin D24 (PC5)
  #define STEPPER_DISABLE_P_4 C // E1 Enable - Pin D30 (PC7)
//  #define STEPPER_DISABLE_P_5
  #define STEPPER_DISABLE_B_0 7 // X Enable - Pin D38 (PD7)
  #define STEPPER_DISABLE_B_1 2 // Y Enable - Pin A2 (PF2)
  #define STEPPER_DISABLE_B_2 0 // Z Enable - Pin A8 (PK0)
  #define STEPPER_DISABLE_B_3 5 // E0 Enable - Pin D24 (PC5)
  #define STEPPER_DISABLE_B_4 7 // E1 Enable - Pin D30 (PC7)
//  #define STEPPER_DISABLE_B_5

  // Define homing/hard limit switch input pins and limit interrupt vectors. 
  #define MIN_LIMIT_P_0 E // X Limit Min - Pin D3 (PE5)
  #define MIN_LIMIT_P_1 J // Y Limit Min - Pin D14 (PJ1)
  #define MIN_LIMIT_P_2 D // Z Limit Min - Pin D18 (PD3)
  #define MIN_LIMIT_B_0 5 // X Limit Min - Pin D3 (PE5)
  #define MIN_LIMIT_B_1 1 // Y Limit Min - Pin D14 (PJ1)
  #define MIN_LIMIT_B_2 3 // Z Limit Min - Pin D18 (PD3)

  #define MAX_LIMIT_P_0 E // X Limit Max - Pin D2 (PE4)
  #define MAX_LIMIT_P_1 J // Y Limit Max - Pin D15 (PJ0)
  #define MAX_LIMIT_P_2 D // Z Limit Max - Pin D19 (PD2)
  #define MAX_LIMIT_B_0 4 // X Limit Max - Pin D2 (PE4)
  #define MAX_LIMIT_B_1 0 // Y Limit Max - Pin D15 (PJ0)
  #define MAX_LIMIT_B_2 2 // Z Limit Max - Pin D19 (PD2)

// xmin INT5
// xmax INT4
// ymin PCINT10 PCINT1_vect PCMSK1/bit(2)
// ymax PCINT9  PCINT1_vect PCMSK1/bit(1)
// zmin INT3
// zmax INT2
  #define DISABLE_HW_LIMITS

  // Define spindle enable and spindle direction output pins.
  #define SPINDLE_ENABLE_P      G
  #define SPINDLE_ENABLE_B      5 // MEGA2560 Digital Pin 4 - Ramps 1.4 Servo 4 Signal pin
  #define SPINDLE_DIRECTION_P   E
  #define SPINDLE_DIRECTION_B   3 // MEGA2560 Digital Pin 5 - Ramps 1.4 Servo 3 Signal pin

  // Define spindle output pins.
  #define SPINDLE_PWM_P   H
  #define SPINDLE_PWM_B   5 // MEGA2560 Digital Pin 8 

  // Define flood and mist coolant enable output pins.
  #define COOLANT_FLOOD_P   B
  #define COOLANT_FLOOD_B   4 // MEGA2560 Digital Pin 10 - Ramps 1.4 12v output
  #define COOLANT_MIST_P    H
  #define COOLANT_MIST_B    6 // MEGA2560 Digital Pin 9 - Ramps 1.4 12v output

  // Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
  #define CONTROL_P      K
  #define CONTROL_B_RESET         1  // Pin A9 - RAMPS Aux 2 Port
  #define CONTROL_B_FEED_HOLD     2  // Pin A10 - RAMPS Aux 2 Port
  #define CONTROL_B_CYCLE_START   3  // Pin A11 - RAMPS Aux 2 Port
  #define CONTROL_B_SAFETY_DOOR   4  // Pin A12 - RAMPS Aux 2 Port
  
// reset       PCINT17 PCINT2_vect PCMSK2/bit(1)
// feed_hold   PCINT18 PCINT2_vect PCMSK2/bit(2)
// cycle_start PCINT19 PCINT2_vect PCMSK2/bit(3)
// safety_door PCINT20 PCINT2_vect PCMSK2/bit(4)
  #define CONTROL_INT_EN_BIT PCIE2  // Pin change interrupt enable pin
  #define CONTROL_INT_vect   PCINT2_vect
  #define CONTROL_INT_PCMSK  PCMSK2 // Pin change interrupt register

  // Define probe switch input pin.
  #define PROBE_P         K
  #define PROBE_B         7  // MEGA2560 Analog Pin 15


  // Advanced Configuration Below You should not need to touch these variables
  // Set Timer up to use TIMER4B which is attached to Digital Pin 8 - Ramps 1.4 12v output with heat sink
  #define SPINDLE_PWM_MAX_VALUE     1024.0 // Translates to about 1.9 kHz PWM frequency at 1/8 prescaler
  #ifndef SPINDLE_PWM_MIN_VALUE
  #define SPINDLE_PWM_MIN_VALUE     1   // Must be greater than zero.
  #endif
  #define SPINDLE_PWM_OFF_VALUE     0

  //Control Digital Pin 6 which is Servo 2 signal pin on Ramps 1.4 board
  #define SPINDLE_TCCRA_REGISTER    TCCR4A
  #define SPINDLE_TCCRB_REGISTER    TCCR4B
  #define SPINDLE_OCR_REGISTER      OCR4C
  #define SPINDLE_COMB_BIT          COM4C1

  // 1/8 Prescaler, 16-bit Fast PWM mode
  #define SPINDLE_TCCRA_INIT_MASK (bit(WGM40) | bit(WGM41))
  #define SPINDLE_TCCRB_INIT_MASK (bit(WGM42) | bit(WGM43) | bit(CS41)) 
  #define SPINDLE_OCRA_REGISTER   OCR4A // 16-bit Fast PWM mode requires top reset value stored here.
  #define SPINDLE_OCRA_TOP_VALUE  0x0400 // PWM counter reset value. Should be the same as PWM_MAX_VALUE in hex.

#endif
/* 
#ifdef CPU_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and edit one of the available cpu
  // map files and modify it to your needs. Make sure the defined name is also changed in
  // the config.h file.
#endif
*/

#endif
