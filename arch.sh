#!/bin/bash

arch=
vendor=pc
os=

case `uname -m` in
  i386|i486|i686) arch=x86 ;;
  x86_64) arch=x86_64 ;;
  *) arch=? ;;
esac

case `uname -o` in
  GNU/Linux) os=linux-gnu ;;
  *) os=unknown ;;
esac


echo $arch-$vendor-$os
