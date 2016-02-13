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
#ifndef _WCTYPE_H
#define _WCTYPE_H 1

// wint_t, wctrans_t, wctype_t

#define _CTYPE(n) int isw ## n(wint_t wc);
#include <skc/ctype.h>
#undef _CTYPE


wint_t towctrans(wint_t wc, wctrans_t desc);
/* Convert letter to upper case */
wint_t towupper(wint_t wc);
/* Convert letter to lower case */
wint_t towlower(wint_t wc);
wctrans_t wctrans(const char *name);
wctype_t wctype(const char *name);


#endif  /* _WCTYPE_H */
