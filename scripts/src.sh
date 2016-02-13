#!/bin/bash

export iso_name=OsCore.iso

clear

while [ -e ./iso ]; do
  sleep 1
  rm -rf ./iso
done

mkdir ./iso
cd ./iso
make -f ../kernel/Makefile kImage NODEPS=1
make -f ../Makefile NODEPS=1

while [ -e ./obj ]; do
  sleep 1
  rm -rf ./obj
done

# Create `boot' directory
mkdir -p ./boot/grub
mv ./kImage ./boot/kImage
cat > ./boot/grub/grub.cfg << EOF
set timeout="0"
menuentry "Smoke_x86" {
  multiboot /boot/kImage
}
EOF

sleep 1

cd ../
grub-mkrescue -o $iso_name iso >/dev/null
ls -lh $iso_name
