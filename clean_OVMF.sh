#!/bin/bash

cd UEFI_Firmware

rm OVMF_VARS.fd

wget https://github.com/uchan-nos/mikanos-build/raw/master/devenv/OVMF_VARS.fd

cd ..