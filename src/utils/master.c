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

int new_syr() 
{
  FILE *fp = NULL;
  fp = fopen(".syr", "w");
  if (!fp)
    return -1;

  fclose(fp);
  return 0;
}

int start_program(const char* command)
{
  FILE *fpipe;
  // char line[256];

  fpipe = (FILE*)popen(command,"r");
  if (!fpipe) {
    fprintf(stderr, "Unable to open the new process: '%s' - [%d] %s.\n", 
        command, errno, strerror(errno));
    return -1;
  }

  // while (fgets(line, sizeof(line), fpipe)) {
  //   printf("%s", line);
  // }
  // pclose(fpipe);
  return 0;
}

int main ()
{
  int lg;
  FILE *fp = NULL;
  char *gt;
  char pwd[PATH_MAX];
  char usr[PATH_MAX];

  fputs("Master " _VTAG_ " \033[30m-- same puporse as init or systemd\033[0m\n", stdout);
  if (getcwd(pwd, PATH_MAX) == NULL) {
    // EACCESS, EFAULT, EINVAL, ENAMETOOLONG, ENOENT, ERANGE
    fprintf(stderr, "Unable to find working directory: [%d] %s.\n", 
        errno, strerror(errno));
    return EXIT_FAILURE;
  }

  fp = fopen(".syr", "r");
  if (fp == NULL) {
    if (errno != ENOENT || new_syr() || !(fp = fopen(".syr", "r"))) {
      fprintf(stderr, "Unable to open system registers: [%d] %s.\n", 
          errno, strerror(errno));
      // return EXIT_FAILURE;
    }
  }

  fputs("System register ready...\n", stdout);
  fputs("Login :: ", stdout);
  gt = fgets(usr, PATH_MAX, stdin);
  if (gt == NULL || gt == (void*)EOF) {
    fputs("\n", stdout);
    fprintf(stderr, "Unable to read user input: [%d] %s.\n", 
        errno, strerror(errno));
    return EXIT_FAILURE;
  }

  lg = strlen(usr);
  if (usr[lg-1] == '\n')
    usr[lg-1] = '\0';

  fprintf(stdout, "\nWelcome %s, you're at %s.\n\n", usr, pwd);
  // start_program("bin/crond");
  // start_program("bin/color");
  start_program("bin/sh");
  return EXIT_SUCCESS;
}


