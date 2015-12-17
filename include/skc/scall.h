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
#ifndef _SKC_SCALL_H
#define _SKC_SCALL_H 1

#define __scc(x) ((long)(x))

/* Concatanation to find marco name */
#define __syscall_concat_x(a,b) a##b
#define __syscall_concat(a,b) __syscall_concat_x(a,b)

/* Count the number of arguments */
#define __syscall_nargs_x(a,b,c,d,e,f,g,h,n,...) n
#define __syscall_nargs(...) __syscall_nargs_x(__VA_ARGS__,7,6,5,4,3,2,1,0)

/* Build macro name */
#define __syscall_x(...)  __syscall_concat(__syscall, __syscall_nargs(__VA_ARGS__))(__VA_ARGS__)
#define __syscall(...)  __syscall_x(__VA_ARGS__)

/* Macro for each number of arguments */
#define __syscall1(n,a) \
    syscall(n,__scc(a))
#define __syscall2(n,a,b) \
    syscall(n,__scc(a),__scc(b))
#define __syscall3(n,a,b,c) \
    syscall(n,__scc(a),__scc(b),__scc(c))
#define __syscall4(n,a,b,c,d) \
    syscall(n,__scc(a),__scc(b),__scc(c),__scc(d))
#define __syscall5(n,a,b,c,d,e) \
    syscall(n,__scc(a),__scc(b),__scc(c),__scc(d),__scc(e))

long syscall(long no, ...);

#define SC_GINFO  0x07
#define SC_EXEC   0x01
/* List of system calls 
#include <bits/syscall.h> */


#endif  /* _SKC_SCALL_H */
