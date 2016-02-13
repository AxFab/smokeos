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
#if !defined _LOCALE_H && !defined _LANGINFO_H
# error "Never use <bits/locale.h> directly; include <locale.h> instead."
#endif

#ifndef _BITS_LOCALE_H
#define _BITS_LOCALE_H  1

enum
{
  LC_CTYPE = 0,
  LC_NUMERIC = 1,
  LC_TIME = 2,
  LC_COLLATE = 3,
  LC_MONETARY = 4,
  LC_MESSAGES = 5,
  LC_ALL = 6,
  LC_PAPER = 7,
  LC_NAME = 8,
  LC_ADDRESS = 9,
  LC_TELEPHONE = 10,
  LC_MEASUREMENT = 11,
  LC_IDENTIFICATION = 12
};

#endif  /* _BITS_LOCALE_H */
