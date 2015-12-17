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
#include <stdio.h>
#include <string.h>
#include <errno.h>

int fgetc_unlocked(FILE *stream)
{
  int c = 0;
  if (stream->read(stream, (char*)&c, 1) == EOF) {
    return EOF;
  }

  return c;
}

char *fgets_unlocked(char *s, int size, FILE *stream)
{
  int c;
  unsigned char *ps = (unsigned char *)s;

  while (--size) {
    c = fgetc_unlocked(stream);
    if (c == EOF) {
      if (errno)
        return NULL;
      break;
    }

    *ps = (unsigned char)c;
    if (c == '\n')
      break;

    ++ps;
  }

  *ps = '\0';
  return ((void*)s == (void*)ps) ? (char*)EOF : s;
}

/* Read a character from STREAM. */
int getc(FILE *stream)
{
  return fgetc(stream);
}

/* Read a character from STREAM. */
int fgetc(FILE *stream)
{
  int c;
  FLOCK(stream);
  c = fgetc_unlocked(stream);
  FUNLOCK(stream);
  return c;
}

/* Get a newline-terminated string of finite length from STREAM. */
char *fgets(char *s, int n, FILE *stream)
{
  FLOCK(stream);
  fgets_unlocked(s, n, stream);
  FUNLOCK(stream);
  return s;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Write a character to STREAM. */
int putc(int c, FILE *stream)
{
  return fputc(c, stream);
}

/* Write a character to STREAM. */
int fputc(int c, FILE *stream)
{
  size_t ret = fwrite(&c, 1, 1, stream);
  return ((int)ret == 1) ? (unsigned char)c : EOF;
}
/* Write a string to STREAM. */
int fputs(const char *s, FILE *stream)
{
  int lg = strlen(s);
  size_t ret = fwrite(s, lg, 1, stream);
  return ((int)ret == lg) ? lg : EOF;
}



/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Read a character from stdin. */
int getchar(void)
{
  return fgetc(stdin);
}

/* Write a character to stdout. */
int putchar(int c)
{
  return fputc(c, stdout);
}

/* Push a character back onto the input buffer of STREAM. */
int ungetc(int c, FILE *stream);

