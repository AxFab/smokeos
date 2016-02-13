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
#ifndef _TCHAR_H
#define _TCHAR_H 1

#if defined __USE_MBS
# include <mbstring.h>
# define _TCHAR unsigned char
# define _SFX(n)  mbs ## n
#elif defined __USE_WCS
# include <wchar.h>
# define _TCHAR wchar_t
# define _SFX(n)  wcs ## n
#else
# include <string.h>
# define _TCHAR char
# define _SFX(n)  str ## n
#endif

typedef _TCHAR TCHAR;

#define tcscat _SFX(cat)
#define tcschr _SFX(chr)
#define tcscmp _SFX(cmp)
#define tcscpy _SFX(cpy)
#define tcscspn _SFX(cspn)
#define tcsicmp _SFX(icmp)
#define tcslen _SFX(len)
#define tcsncat _SFX(ncat)
#define tcsncmp _SFX(ncmp)
#define tcsncpy _SFX(ncpy)
#define tcspbrk _SFX(pbrk)

#undef _TCHAR
#undef _SFX

#endif  /* _TCHAR_H */
