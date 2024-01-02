/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdarg.h>
#include <rawfloat.c>
#include <string.h>

#define ZEROPAD    (1<<0)  /* Pad with zero */
#define SIGN      (1<<1)  /* Unsigned/signed long */
#define PLUS      (1<<2)  /* Show plus */
#define SPACE     (1<<3)  /* Spacer */
#define LEFT      (1<<4)  /* Left justified */
#define HEX_PREP  (1<<5)  /* 0x */
#define UPPERCASE   (1<<6)  /* 'ABCDEF' */
#define HAS_FLOAT 1

#define is_digit(c) ((c) >= '0' && (c) <= '9')




  extern int sprintf(char * buffer,const char *fmt, ...);
  int ee_vsprintf(char *buf, const char *fmt, va_list args);
  int skip_atoi(const char **s);
  char *number(char *str, long num, int base, int size, int precision, int type);
  char *eaddr(char *str, unsigned char *addr, int size, int precision, int type);
  char *iaddr(char *str, unsigned char *addr, int size, int precision, int type);
  char *flt(char *str, double num, int size, int precision, char fmt, int flags);
  void parse_float(double value, char *buffer, char fmt, int precision);
  void decimal_point(char *buffer);
  void cropzeros(char *buffer);
  char *ecvtbuf(double arg, int ndigits, int *decpt, int *sign, char *buf);
  char *fcvtbuf(double arg, int ndigits, int *decpt, int *sign, char *buf);
  void ee_bufcpy(char *d, char *s, int count); 
