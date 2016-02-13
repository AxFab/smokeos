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
 *   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int new_thread (void(*start)(long), long param);

void do_nothing()
{
}

void count(long until)
{
  int i, j;

  for (i = 0; i <= until; ++i) {
    fprintf(stdout, "Count is %d/%d.\n", i, until);
    for (j = 0 ; j < 0x80000; ++j)
      do_nothing();
  }
}

int main() 
{
  fputs("crond " _VTAG_ "\n", stdout);
  // new_thread(count, 8);
  // new_thread(count, 6);
  // new_thread(count, 9);
  count (7);
  return EXIT_SUCCESS;
}

