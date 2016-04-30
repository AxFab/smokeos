#include <sys/types.h>
#include <skc/iofile.h>
#include <skc/scall.h>
#include <skc/mcrs.h>
#include <stdarg.h>


int open(const char *name, int flags, ...)
{
  int mode;
  va_list ap;
  
  va_start(ap, flags);
  mode = va_arg(ap, int);
  va_end(ap);

  return __syscall(0x21, name, -1, flags, mode);
}

int close(int fd)
{
  return __syscall(0x20, fd);
}

int read(int fd, char *buf, size_t count)
{
  return __syscall(0x22, fd, buf, count, -1);
}

int write(int fd, const char *buf, size_t count)
{
  return __syscall(0x23, fd, buf, count, -1);
}

int lseek(int fd, off_t offset, unsigned int origin)
{
  return __syscall(0x24, fd, offset, origin);
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */


/* Remove file FILENAME.  */
int remove(const char *filename)
{
  return __syscall(0x30, EOF, filename);
}

/* Rename file OLD to NEW.  */
int rename(const char *oldFn, const char *newFn)
{
  return __syscall(0x31, EOF, oldFn, EOF, newFn);
}



int fcntl(int fd, int cmd, ...) 
{
  return -1;
}

