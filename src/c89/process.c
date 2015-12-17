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
#ifndef __USE_SCALL
# error "This source file can't be used without syscalls."
#endif

 
/* Cause abnormal process termination */
void abort(void);
/* Cause normal process termination */
void exit(int status);
/* Get an environment variable */
char *getenv(const char *name);
/* Execute a shell command */
int system(const char *command);
/* Register a function to be called at normal process termination. */
int atexit(void (*function)(void));

