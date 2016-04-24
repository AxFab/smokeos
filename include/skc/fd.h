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
#ifndef _SKC_FD_H
#define _SKC_FD_H 1

#ifndef __USE_SCALL
# error "This source file can't be used without syscalls."
#endif

int open(const char*, int, ...);
int close(int);
int read(int fd, void *buf, size_t count); 
int write(int fd, const void *buf, size_t count);
int lseek(int fd, off_t offset, unsigned int origin);

#endif  /* _SKC_FD_H */
