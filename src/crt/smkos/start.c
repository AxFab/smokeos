#include <skc/iofile.h>
#include <fcntl.h>
#include <skc/scall.h>
#include <skc/mcrs.h>
#include <skc/mmap.h>


/* Function to get address of global `errno' variable.  */
int *__errno_location(void)
{
  static int __errno;
  return &__errno;
}

char *__progname;


int __std_argc;
char **__std_argv;
char **environ;

FILE *stdin;
FILE *stdout;
FILE *stderr;

void* __heap_start;
void* __heap_end;

void __malloc_init(void* base, size_t len);

void __std_start(void) 
{
  __progname = "?";
  __std_argv = &__progname;
  __std_argc = 1;

  __heap_start = manmap(4 * _Mib_, PROT_READ | PROT_WRITE);
  __heap_end = (void*)((long)__heap_start + 4 * _Mib_);
  __malloc_init(__heap_start, 4 * _Mib_);

  stdin = fvopen(0, O_RDONLY | O_CLOEXEC);
  stdout = fvopen(1, O_RDONLY | O_CLOEXEC);
  stderr = fvopen(2, O_RDONLY | O_CLOEXEC);
}
