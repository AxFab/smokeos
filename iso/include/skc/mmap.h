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
#ifndef _SKC_MMAP_H
#define _SKC_MMAP_H 1

#include <stddef.h>

#ifdef __USE_SCALL
#include <sys/mman.h>
// void *mmap(void *addr, size_t lg, int prot, int flags, int fd, off_t offset);
#else
#include <sys/types.h>
int munmap(void *addr, size_t lg);
#endif

void *manmap(size_t lg, int prot);


#endif  /* _SKC_MMAP_H */
