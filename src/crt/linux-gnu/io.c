#include <stdarg.h>
#include <sys/types.h>
#include <skc/iofile.h>
#include <skc/scall.h>
#include <skc/mcrs.h>


int open(const char *name, int flags, ...)
{
  int mode;
  va_list ap;
  
  va_start(ap, flags);
  mode = va_arg(ap, int);
  va_end(ap);

  return __syscall(0x05, name, flags, mode);
}

int close(int fd)
{
  return __syscall(0x06, fd);
}

int read(int fd, char *buf, size_t count)
{
  return __syscall(0x3, fd, buf, count);
}

int write(int fd, const char *buf, size_t count)
{
  return __syscall(0x4, fd, buf, count);
}

int lseek(unsigned int fd, off_t offset, unsigned int origin)
{
  return __syscall(0x13, fd, offset, origin);
}

