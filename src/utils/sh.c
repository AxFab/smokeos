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
// #include <unistd.h>

char *getcwd(char *buf, size_t size);
int getlogin_r(char *buf, size_t bufsize);

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
  //  -- or
  // waitpid()
  return 0;
}

int main ()
{
  char pwd[PATH_MAX];
  char usr[PATH_MAX];
  char cmd[PATH_MAX];
  char *gt;

  fputs("Shell " _VTAG_ " \033[30m-- this is a basic shell for kernel development\033[0m\n", stdout);

  // Find PWD
  if (getcwd(pwd, PATH_MAX) == NULL) {
    // EACCESS, EFAULT, EINVAL, ENAMETOOLONG, ENOENT, ERANGE
    fprintf(stderr, "Unable to find working directory: [%d] %s.\n",
        errno, strerror(errno));
    return EXIT_FAILURE;
  }

  // Find USERNAME
  if (getlogin_r(usr, PATH_MAX)) {
    // EACCESS, EFAULT, EINVAL, ENAMETOOLONG, ENOENT, ERANGE
    fprintf(stderr, "Unable to find username: [%d] %s.\n",
        errno, strerror(errno));
    return EXIT_FAILURE;
  }


  fprintf(stdout, "Welcome '%s', you're at '%s'.\n", usr, pwd);
  for (;;) {
    fprintf(stdout, "%s@host:%s > ", usr, pwd);
    gt = fgets(cmd, PATH_MAX, stdin);
    if (gt == NULL || gt == (void*)EOF) {
      fputs("\n", stdout);
      fprintf(stderr, "Unable to read user input: [%d] %s.\n",
          errno, strerror(errno));
      return EXIT_FAILURE;
    }

    start_program(cmd);
  }

  return EXIT_SUCCESS;
}


