#!/bin/bash

export iso_name=OsCore.iso
export ret=0
export smkos=.

# Cleanup
clear
rm -rf iso
mkdir -p iso/{bin,boot/grub}

# Build the kernel
make -f $smkos/kernel/Makefile kImage gendir=$smkos/iso target=x86-pc-smkos NODEPS=1
if [ $? -ne 0 ]; then
  echo "ERROR :: Build kernel failed." 1>&2
  exit -1
fi

# Build utilities
make -f $smkos/Makefile gendir=$smkos/iso target=x86-pc-smkos NODEPS=1
if [ $? -ne 0 ]; then
  echo "ERROR :: Build utilities failed." 1>&2
  exit -1
fi

mv iso/kImage iso/boot/kImage
cp scripts/grub.cfg iso/boot/grub/grub.cfg
cp -r include iso/
rm -rf iso/obj

# Create ISO file
echo "    ISO "$iso_name
grub-mkrescue -o $iso_name iso >/dev/null
if [ $? -ne 0 ]; then
  echo "ERROR :: Can't create iso file"
fi

rm -rf obj lib
ls -lh $iso_name

