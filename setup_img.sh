#!/bin/bash

cd edk2
source edksetup.sh

# for cleanly updating
rm -rf KlpsLoaderPkg
rm -rf Build

# Use -r option to recursively copy 'app' directory
cp -r ../app KlpsLoaderPkg
cp ../target.txt Conf/target.txt

# in case
make -C /workspaces/KalapagosOS/edk2/BaseTools/Source/C

# build pkg
build

# Don't forget to set TARGET in target.txt to KlpsLoaderPkg/KlpsLoaderPkg.dsc
# OvmfPkg/OvmfPkgX64.dsc is for OVMF.fd
cd ..

src="edk2/Build/KlpsLoaderPkgX64/RELEASE_GCC5/X64/KlpsLoaderPkg/applications/src/main/OUTPUT/Main.efi"
BOOTX64Path="img/EFI/BOOT/BOOTX64.efi"

# Corrected the variable name and added destination file
cp "$src" "$BOOTX64Path"
