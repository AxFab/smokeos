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
#ifndef _STDIO_H
#define _STDIO_H 1

#include <stddef.h>

#define _XCHAR  char
#include <skc/iostm.h>
#undef _XCHAR

#include <bits/iolimits.h>
#include <skc/libio.h>

/* Get a newline-terminated string from stdin, removing the newline.
   DO NOT USE THIS FUNCTION!!  There is no limit on how much it will read. */
char *gets (char *s);
/* Write a string, followed by a newline, to stdout. */
int puts (const char *s);



/* Print a message describing the meaning of the value of errno. */
void perror(const char *s);
/* Remove file FILENAME.  */
int remove(const char *filename);
/* Rename file OLD to NEW.  */
int rename(const char *oldFn, const char *newFn);


/* tmpfile, tmpnam */
/* Generate and open a new temporary file */ 
FILE *tmpfile(void);
/* Generate a new name for a tempoary file */
char *tmpnam(char *);
char *tmpnam_r(char *);


extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;


#ifdef __USE_EXT

/* Pipe stream to or from a process */
FILE *popen(const char *command, const char *mode);


#endif

#endif  /* _STDIO_H */
