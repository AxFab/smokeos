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
#include <bits/ctype.h>
#include "ctype_ascii.h"

#define _CHAR(c) ((int)((char)(c)))
#define _CTYPE(n) int is ## n (int c) \
    { return (__ascii_ctype()[_CHAR(c)] & _IS ## n) ? 1 : 0; }

#include <skc/ctype.h>


/* Convert letter to upper case */
int toupper(int c)
{
  return __ascii_upper()[_CHAR(c)];
}

/* Convert letter to lower case */
int tolower(int c)
{
  return __ascii_lower()[_CHAR(c)];
}


