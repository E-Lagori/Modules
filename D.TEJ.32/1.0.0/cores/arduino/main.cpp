/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  This code has been modified by SiFive, Inc, in order to support
  the SiFive Freedom E300 Platform development boards.
*/

#define ARDUINO_MAIN
#include "Arduino.h"
#include "encoding.h"


extern uint32_t trap_entry;

#define cmb() __asm__ __volatile__ ("" ::: "memory")




void aries_specific_initialization(void)
{

  write_csr(mtvec, &trap_entry);
  
}






/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{

  aries_specific_initialization();
  setup();
  
  do {

    loop();
    //if (serialEventRun)
    //  serialEventRun();
  } while (1);
  
  return 0;
}
