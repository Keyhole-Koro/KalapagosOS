#!/bin/bash

cd edk2
source edksetup.sh

# Use -r option to recursively copy 'app' directory
cp -r ../app/KlpsPkg
cp ../target.txt Conf/target.txt

rm -rf Build

# in case
make -C /workspaces/KalapagosOS/edk2/BaseTools/Source/C

# Assuming 'build' is the correct build command, replace it accordingly if it's different
build 

# Don't forget to set TARGET in target.txt to KlpsPkg/KlpsPkg.dsc
# OvmfPkg/OvmfPkgX64.dsc is for OVMF.fd
cd ..

src="edk2/Build/KlpsPkgX64/RELEASE_GCC5/X64/KlpsPkg/applications/src/main/OUTPUT/Main.efi"
BOOTX64Path="img/EFI/BOOT/BOOTX64.sh"

# Corrected the variable name and added destination file
cp "$src" "$BOOTX64Path"
