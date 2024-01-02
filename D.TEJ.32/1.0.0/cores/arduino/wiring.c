/*-
 * Copyright (c) 2015 Marko Zec, University of Zagreb
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id$
 */

#include "Arduino.h"
#include "platform.h"
#include "encoding.h"


unsigned long millis() {

  unsigned long long current_clock_count;
  unsigned long long clk_cnt_msb; 
  unsigned long long clk_cnt_lsb;

  clk_cnt_lsb = read_csr(mcycle);
  clk_cnt_msb = read_csr(mcycleh);
  current_clock_count = (clk_cnt_msb << 32) | clk_cnt_lsb;
  return (((current_clock_count) * 0.0101)/1000);
}


unsigned long micros(void) {

  unsigned long long current_clock_count;
  unsigned long long clk_cnt_msb; 
  unsigned long long clk_cnt_lsb;

  clk_cnt_lsb = read_csr(mcycle);
  clk_cnt_msb = read_csr(mcycleh);
  current_clock_count = (clk_cnt_msb << 32) | clk_cnt_lsb;
  return (current_clock_count * 0.0101);
}


void delay(unsigned long  ms) {

  asm volatile("mv a5,%0\n\t"
    "li a6,1 \n\t"
    "beq a5,a6,final\n\t"
    "li a6,3 \n\t"
    "bge a5,a6,cycle_loop\n\t"
    "nop\n\t"
    "nop\n\t"
    "bnez a5,loop\n\t"
    "j final\n\t"
    "mul a4,a5,a4\n\t"
    //"csrr a6,mcycle\n\t"
    "bnez a4,loop1\n\t"
    //"addi a5,a5,-1\n\t"
    //"bnez a5,cycle_loop\n\t"
    : : "r"(ms*1000) : "a5" );
    }

void delayMicroseconds(unsigned long us) {

 asm volatile("mv a5,%0\n\t"
	"li a6,1 \n\t"
	"beq a5,a6,final\n\t"
	"li a6,3 \n\t"
	"bge a5,a6,cycle_loop\n\t"
	"loop: addi a5,a5,-1\n\t"
	"nop\n\t"
	"nop\n\t"
	"bnez a5,loop\n\t"
	"j final\n\t"
	"cycle_loop: li a4,33\n\t"
	"mul a4,a5,a4\n\t"
	//"csrr a6,mcycle\n\t"
	"loop1: addi a4,a4,-1\n\t"	
	"bnez a4,loop1\n\t"
	//"addi a5,a5,-1\n\t"
	//"bnez a5,cycle_loop\n\t"
	"final:\n\t"
	: : "r"(us) : "a5" );
}
