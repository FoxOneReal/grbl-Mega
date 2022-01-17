/*
  ext_int.h - External interrupts handling
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
#ifndef ext_int_h
#define ext_int_h

#define LOW_LEVEL_TRIGGER    0
#define LEVEL_CHANGE_TRIGGER 1
#define FALLING_EDGE_TRIGGER 2
#define RISING_EDGE_TRIGGER  3

#define HANDLER_SYSTEM 0
#define HANDLER_LIMITS 1

void int_init();

void int_enable( char port, uint8_t bit, uint8_t trigger, uint8_t handler );

void int_disable( char port, uint8_t bit );

#endif
