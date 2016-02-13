SmokeOS is a hobbyist operating system. For the moment only the kernel is worth mention.

## Obtaining the kernel source

The kernel code is available on [Github](https://github.com/AxFab/kernel). If you plan to work with the kernel, you should always start from the last version of `master` (eq. to `develop` for git-flows users). If you wish to use a more reliable version of the kernel the you should use the last version of the branch `stable`. Stable version are also available as tarballs which provide an easy way to update the kernel.

## Kernel source tree

The kernel tree is pretty simple.

__name__|__purpose__
----|-------
src/fs|File system
src/kern|Kernel core
src/asm|Platform dependent code
src/libc|Partial implementation of the libc
include/asm|Platform dependent header
include/smkos|Kernel headers

