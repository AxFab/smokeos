#include <skc/iofile.h>
#include <skc/scall.h>
#include <skc/mcrs.h>
#include <sys/types.h>
#include <string.h>


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
  struct mmap_arg_struct arg;
  arg.addr = (unsigned long)addr;
  arg.len = lg;
  arg.prot = prot;
  arg.flags = flags;
  arg.fd = fd;
  arg.offset = offset;
  return (void*)__syscall(0x5a, &arg);
}






/* Get current working directory */
char *getcwd(char *buf, size_t size)
{
  __syscall(0xb7, buf, size);
  return buf;
}

int getuid(void) 
{
  return __syscall(0xc7, 0);
}

/* Get current username */
int getlogin_r(char *buf, size_t size)
{
  strncpy(buf, "root", size);
  return 0;
}

