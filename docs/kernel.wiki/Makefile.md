## Makefile

### The generic script

 The first block is the configuration for the project: name, version, target, host, date...

 This is follow by 3 variable named S(silent), Q(quiet), V(verbose).
 Those allow to set the verbosity of the script. S is always silent, 
 Q is enable by default unless `QUIET=1`. V is disable by default 
 unless `VERBOSE=1`. We use S for minor command (like `mkdir`), 
 Q usally print a simply form of the command to list created file.
 Important command are display only using verbose mode.

 Second block list all used directories. All depends on the tree configurable ones: `prefix`, `topdir` and `gendir` for install 
 directory, repository directory and build directory.

### Can I use configure

 This makefile doesn't need a configure script. you can use `make -f`
 on the build dir and select the repository makefile to build without
 change to the sources directory. However it might be easier to get a
 Makefile to save paths and configs. Just copy past this script and
 replace `${PWD}` by the build directory path, ${SRC} by the
 repository path, then adjust the settings. With this, you will just
 have to do `make`.

    # Configure script
    build = x86_64-pc-linux-gnu
    host = x86-pc-smkos
    target = $(host)
    prefix = /usr/local
    topdir = ${SRC}
    gendir = ${PWD}
    VERBOSE =
    QUIET =
    NODEPS =
    include $(topdir)/Makefile


### Create a new image
  
    # Select sources
    monImage_src-y += $(wildcard $(srcdir)/kern/*.c)
    monImage_src-y += ...
    monImage_src-y += $(kfs_src-y)
    monImage_CFLAGS += $(CFLAGS)
    monImage_CFLAGS += ...
    monImage_LFLAGS += -nostdlib
    monImage_LFLAGS += ...
    $(eval $(call ccpl,monImage))
    $(eval $(call kimg,monImage,monImage))
    DV_UTILS += $(gendir)/monImage

