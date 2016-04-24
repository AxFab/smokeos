#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <skc/mmap.h>
#include <skc/scall.h>

int vdprintf(int fd, const char *format, va_list ap);
void __fxprintf(int fd, const char *msg, ...)
{
  va_list ap;
  va_start(ap, msg);
  if (fd < 0)
    fd = 2; // stderr
  vdprintf(fd, msg, ap);
  va_end(ap);
}

void abort(void)
{
  for(;;);
}

void *manmap(size_t lg, int prot)
{
  int flags = MAP_PRIVATE | MAP_ANONYMOUS;
  return mmap(NULL, lg, prot, flags, -1, 0);
}

int munmap(void *addr, size_t lg)
{
  errno = ENOSYS;
  return -1;
}


/* Determine processor time */
clock_t clock(void);

/* Get time in seconds  */
time_t time(time_t *p)
{
  time_t s;
  __syscall(0x0d, &s);
  if (p) 
    *p = s;
  return s;
}


void exit(int code) {
  __syscall(0x1, code);
}

