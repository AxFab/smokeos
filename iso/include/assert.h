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
#ifndef _ASSERT_H
#define _ASSERT_H 1

#include <bits/cdefs.h>

#undef assert
#ifdef NDEBUG
# define assert(ignore) ((void) 0)
# define assert_msg(ignore) ((void) 0)
#else
# define assert(e)       ((e)?(void)0:__assert_fail(#e,__FILE__,__LINE__,""))
# define assert_msg(e,m) ((e)?(void)0:__assert_fail(m,__FILE__,__LINE__,""))
#endif

/* If the assertion test is false, the program will print the reason for
  * the assertion an leave the program. in other case this routines have no
  * effect. */
__NORET void __assert_fail(const char *expr, const char *file, int line,
                   const char *func);

#endif  /* _ASSERT_H */
