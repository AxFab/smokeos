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
#ifndef _PRV_DIAGNOSTICS_H
#define _PRV_DIAGNOSTICS_H 1 

#include <assert.h>
#include <stddef.h>

void __fxprintf(int fd, const char *msg, ...);

extern char *__progname;

__NORET void abort(void);

int strerror_r(int err, char *buf, size_t lg);

#endif /* _PRV_DIAGNOSTICS_H */
