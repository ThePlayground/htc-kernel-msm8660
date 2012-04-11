#!/bin/bash

# Copyright (C) 2011 Twisted Playground

# This script is designed by Twisted Playground for use on MacOSX 10.7 but can be modified for other distributions of Mac and Linux

PROPER=`echo $2 | sed 's/\([a-z]\)\([a-zA-Z0-9]*\)/\u\1\2/g'`

HANDLE=TwistedZero
KERNELSPEC=/Volumes/android/htc-kernel-msm8660
ANDROIDREPO=/Volumes/android/Twisted-Playground
TOOLCHAINDIR=/Volumes/android/android-tzb_ics4.0.1/prebuilt/darwin-x86/toolchain/arm-eabi-4.4.3/bin
DROIDGITHUB=TwistedUmbrella/Twisted-Playground.git
SHOOTREPO=/Volumes/android/github-aosp_source/android_device_htc_shooter
SHOOTGITHUB=ThePlayground/android_device_htc_shooter.git
ICSREPO=/Volumes/android/github-aosp_source/android_system_core
MSMREPO=/Volumes/android/github-aosp_source/android_device_htc_msm8660-common
zipfile=$HANDLE"_teamevo-hijack_ICS.zip"

CPU_JOB_NUM=16
TOOLCHAIN_PREFIX=$TOOLCHAINDIR/arm-eabi-

echo "Config Name? "
ls config
read configfile
cp -R config/$configfile .config

make clean -j$CPU_JOB_NUM

make -j$CPU_JOB_NUM ARCH=arm CROSS_COMPILE=$TOOLCHAIN_PREFIX

find . -name "*.ko" | xargs ${TOOLCHAIN_PREFIX}strip --strip-unneeded

if [ -e arch/arm/boot/zImage ]; then

if [ "$1" == "1" ]; then

echo "adding to build"

cp -R arch/arm/boot/zImage $SHOOTREPO/prebuilt/root/kernel
rm -r $SHOOTREPO/prebuilt/system/lib/modules/*
for j in $(find . -name "*.ko"); do
cp "${j}" $SHOOTREPO/prebuilt/system/lib/modules
done

cd $SHOOTREPO
git commit -a -m "Automated Kernel Update - ${PROPER}"
git push git@github.com:$SHOOTGITHUB HEAD:ics

else

cp -R $ICSREPO/rootdir/init.rc $KERNELSPEC/mkboot.aosp/boot.img-ramdisk
cp -R $ICSREPO/rootdir/ueventd.rc $KERNELSPEC/mkboot.aosp/boot.img-ramdisk
cp -R $SHOOTREPO/prebuilt/root/init.shooter.rc $KERNELSPEC/mkboot.aosp/boot.img-ramdisk
cp -R $SHOOTREPO/prebuilt/root/ueventd.shooter.rc $KERNELSPEC/mkboot.aosp/boot.img-ramdisk
cp -R $MSMREPO/prebuilt/init.msm8660.usb.rc $KERNELSPEC/mkboot.aosp/boot.img-ramdisk

if [ ! -e zip.aosp/system/lib ]; then
mkdir zip.aosp/system/lib
fi
if [ ! -e zip.aosp/system/lib/modules ]; then
mkdir zip.aosp/system/lib/modules
else
rm -r zip.aosp/system/lib/modules
mkdir zip.aosp/system/lib/modules
fi

for j in $(find . -name "*.ko"); do
cp -R "${j}" zip.aosp/system/lib/modules
done
cp -R arch/arm/boot/zImage mkboot.aosp

cd mkboot.aosp
echo "making boot image"
./img.sh

echo "making zip file"
cp -R boot.img ../zip.aosp
cd ../zip.aosp
rm *.zip
zip -r $zipfile *
cp -R $KERNELSPEC/zip.aosp/$zipfile $ANDROIDREPO/Kernel/$zipfile
cd $ANDROIDREPO
git checkout gh-pages
git commit -a -m "Automated Patch Kernel Build - ${PROPER}"
git push git@github.com:$DROIDGITHUB HEAD:ics -f

fi

fi

cd $KERNELSPEC