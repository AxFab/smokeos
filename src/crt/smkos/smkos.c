#include <stdio.h>
#include <errno.h>
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
time_t time(time_t *p);



struct mmap_arg_struct {
  unsigned long addr;
  unsigned long len;
  unsigned long prot;
  unsigned long flags;
  unsigned long fd;
  unsigned long offset;
};

void *mmap(void *addr, size_t lg, int prot, int flags, int fd, off_t offset)
{
  // struct mmap_arg_struct arg;
  // arg.addr = (unsigned long)addr;
  // arg.len = lg;
  // arg.prot = prot;
  // arg.flags = flags;
  // arg.fd = fd;
  // arg.offset = offset;
  // return (void*)__syscall(0x19, &arg);
  return (void*)__syscall(0x19, fd, addr, lg, offset, prot | flags);
}




#define SI_PWD  1
#define SI_UID  3
#define SI_USERNAME  2

/* Get current working directory */
char *getcwd(char *buf, size_t size)
{
  __syscall(0x18, buf, size, SI_PWD);
  return buf;
}

int getuid(void) 
{
  int uid;
  __syscall(0x18, &uid, 4, SI_UID);
  return uid;
}

/* Get current username */
int getlogin_r(char *buf, size_t size)
{
  return __syscall(0x18, buf, size, SI_USERNAME);
}

