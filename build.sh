#!/bin/bash

export iso_name=OsCore.iso
export target=x86-pc-smkos
# export VERBOSE=1
export NODEPS=1

rm -rf iso
mkdir iso
cd iso

make -f ../Makefile topdir=../ gendir=.
make -f ../kernel/Makefile topdir=../kernel gendir=. kImage

cd ..

mkdir -p iso/boot/grub
mv iso/kImage iso/boot/kImage 
mv iso/kImage.map iso/boot/kImage.map
rm -rf iso/obj
cat >  iso/boot/grub/grub.cfg << EOF
set timeout=0

menuentry "Smoke_x86" {
  multiboot /boot/kImage boot=casper integrity-check quiet splash 
}
EOF

grub-mkrescue -o $iso_name iso >/dev/null
ls -l $iso_name

