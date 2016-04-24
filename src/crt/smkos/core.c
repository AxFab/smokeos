#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <skc/mmap.h>
#include <skc/scall.h>


void exit(int code) {
  __syscall(0x10, code, 0);
}

