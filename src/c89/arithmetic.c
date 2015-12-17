/*
 *      This file is part of the SmokeOS project.
 *  Copyright (C) 2015  <Fabien Bavent>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   - - - - - - - - - - - - - - -
 */
#include <stdlib.h>


/* Compute the absolute value of an integer */ 
int abs(int j)
{
  return j >= 0 ? j : -j;
}

/* Compute quotient and remainder of an integer division */
div_t div(int numerator, int denominator)
{
  div_t res;
  res.quot = numerator / denominator;
  res.rem = numerator % denominator;
  return res;
}

/* Compute the absolute value of an integer */
long int labs(long int j)
{
  return j >= 0 ? j : -j;
}

/* Compute quotient and remainder of an integer division */
ldiv_t ldiv(long numerator, long denominator)
{
  ldiv_t res;
  res.quot = numerator / denominator;
  res.rem = numerator % denominator;
  return res;
}

#ifdef __USE_C99
/* Compute the absolute value of an integer */
long long int llabs(long long int j)
{
  return j >= 0 ? j : -j;
}

/* Compute quotient and remainder of an integer division */
lldiv_t lldiv(long long numerator, long long denominator)
{
  lldiv_t res;
  res.quot = numerator / denominator;
  res.rem = numerator % denominator;
  return res;
}

#endif
