
use32

global _start, start, syscall
extern __std_argc, __std_argv, environ
extern __std_start, main


_start:
start:
  ;pop eax ; Get the number of arguments
  ;mov [__std_argc], eax
  ;mov [__std_argv], esp ; Arguments vector
  sub esp, 0x10
  and esp, ~0xF

  call __std_start
  mov dword [esp], __std_argc
  mov dword [esp + 4], __std_argv
  mov dword [esp + 8], environ
  call main ; call main

  mov ecx, eax ; Put errcode in arg0
  xor edx, edx
  mov eax, 0x10 ; Select EXIT sycall
  int 0x30 ; call sys_exit
  jmp $


syscall:
  pop eax ; eip
  pop eax ; arg 0
  pop ecx ; arg 1
  pop edx ; ...
  pop ebx
  pop esi
  pop edi
  int 0x30
  sub esp, 7*4
  ret

