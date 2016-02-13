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
#ifndef _WCHAR_H
#define _WCHAR_H 1

#include <stddef.h>


#define _TVOID  wchar_t
#define _TCHAR  wchar_t
#define _SFM(n)  wmem ## n
#define _SFX(n)  wsc ## n
#include <skc/string.h>
#undef _TVOID
#undef _TCHAR
#undef _SFM
#undef _SFX


#define _XIO  w
#define _XCHAR  wchar_t
#include <skc/iostm.h>
#undef _XIO
#undef _XCHAR

/*
  btowc
  fwide
  mbrlen
  mbrtowc
  mbsinit
  mbsrtowcs
  wcrtomb

  wcsftime
  wcsrtombs

  wcstod
  wcstol
  wcstoul

  wctob 
*/

#endif  /* _WCHAR_H */
