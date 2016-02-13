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
#ifndef _MBSTRING_H
#define _MBSTRING_H 1

#include <stddef.h>

#define _TVOID unsigned char
#define _TCHAR unsigned char
#define _SFM(n)  mbmem ## n
#define _SFX(n)  mbs ## n
#include <skc/string.h>
#undef _TVOID
#undef _TCHAR
#undef _SFM
#undef _SFX



#endif  /* _MBSTRING_H */
