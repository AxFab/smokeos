#include <skc/iofile.h>
#include <fcntl.h>
#include <skc/scall.h>
#include <skc/mcrs.h>

int __std_argc;
char **__std_argv;
char **environ;

FILE *stdin;
FILE *stdout;
FILE *stderr;

void* __heap_start;
void* __heap_end;

void __malloc_init(void* base, size_t len);

void* brk(long len)
{
  return (void*)__syscall(0x2d, len);
}

void __std_start(void) {
  __heap_start = brk(0);
  __heap_end = brk((long)__heap_start + 4 * _Mib_);
  __malloc_init(__heap_start, 4 * _Mib_);

  stdin = fvopen(0, O_RDONLY | O_CLOEXEC);
  stdout = fvopen(1, O_RDONLY | O_CLOEXEC);
  stderr = fvopen(2, O_RDONLY | O_CLOEXEC);
}


int read(int fd, char *buf, size_t count)
{
  return __syscall(0x3, fd, buf, count);
}

int write(int fd, const char *buf, size_t count)
{
  return __syscall(0x4, fd, buf, count);
}








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