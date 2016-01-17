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
#include <errno.h>
#include <string.h>
#include <skc/scall.h>
#include <bits/cdefs.h>

#define PATH_MAX 8192
#define GI_PWD 1

/* Get current working directory 
char *getcwd(char *buf, size_t size)
{
  static char tmp[PATH_MAX];
  __syscall(SC_GINFO, tmp, PATH_MAX, GI_PWD);
  strncpy(buf, tmp, size);
  return buf;
}
*/
int close(int);

int pipe(int tty[2])
{
  tty[0] = -1;
  tty[1] = -1;
  return 0;
}


typedef struct pstart {
  int exec_;
  const char *cmd_;
  int input_;
  int output_;
  int error_;
} pstart_t;

int exec(const char *command, pstart_t* info)
{
  // int fd = open(command);
  // io->exec_ = fd;
  // info->cmd_ = command;
  return (int)__syscall(0x11, command, info);
  // errno = ENOSYS;
  // return -1;
}

/* Pipe stream to or from a process */
FILE *popen(const char *command, const char *mode)
{
  int md;
  FILE* fp;
  pstart_t info;
  int tty[2]; 

  md = oflags(mode);
  if (md < 0 || pipe(tty) || strlen(command) <= 0)
    return NULL;

  memset(&info, 0, sizeof(info));
  info.input_ = tty[0];
  info.output_ = tty[1];
  info.error_ = tty[1];
  int pid = exec(command, &info);
  if (pid < 0) {
    close(tty[0]);
    close(tty[1]);
    return NULL;
  }

  fp = fvopen(tty[1], md);
  return fp;
}

int pclose(struct _IO_FILE* fp)
{
  return fclose(fp);
}
