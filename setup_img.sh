#!/bin/sh
cp app edk2/KlpsPkg
cp target.txt edk2/Conf/target.txt

cd edk2
source edksetup.sh

rm -rf Build

build # Don't forget to set TARGET in target.txt to KlpsPkg/KlpsPkg.dsc
# OvmfPkg/OvmfPkgX64.dsc is for OVMF.fd
cd ..

src="edk2/Build/KlpsPkgX64/RELEASE_GCC5/X64/KlpsPkg/applications/src/main/OUTPUT/Main.efi"
BOOTX64Path="img/EFI/BOOT/BOOTX64.sh"

cp $src $BOOTX64ELFPath