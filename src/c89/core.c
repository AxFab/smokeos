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
#include <errno.h>
#include "core.h"

#define SEPARATOR_IF(s) ((s)[0]?": ":"")

/** If the assertion test is false, the program will print the reason for
  * the assertion an leave the program. in other case this routines have no
  * effect. */
__NORET void __assert_fail(const char *expr, const char *file, int line,
                           const char *func)
{
  static const char *msg = "%s%s%s: %u: %s%sAssertion `%s'\n";
  __fxprintf(0, msg, __progname, SEPARATOR_IF(__progname),
    file, line, func, SEPARATOR_IF(func), expr);
  abort();
}


__NORET void __perror_fail(int errnum, const char *file, int line,
                           const char *func)
{
  char errbuf[64];
  static const char *msg = "%s%s%s: %u: %s%sUnexpected error `%s' (%u)\n";
  __fxprintf(0, msg, __progname, SEPARATOR_IF(__progname),
    file, line, func, SEPARATOR_IF(func), 
    strerror_r(errnum, errbuf, sizeof (errbuf)), errnum);
  abort();
}


/* Print a message describing the meaning of the value of errno. */
void perror(const char *s)
{
  char errbuf[64];
  static const char *msg = "%s%s Unexpected error `%s' (%u): %s\n";
  __fxprintf(0, msg, __progname, SEPARATOR_IF(__progname),
    strerror_r(errno, errbuf, sizeof (errbuf)), errno, s);
}


/* Terminate a function in case of stack overflow */
void __stack_chk_fail(void)
{
  static const char *msg = "%s%s Stack overflow \n";
  __fxprintf(0, msg, __progname, SEPARATOR_IF(__progname));
  abort();
}

