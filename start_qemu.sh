qemu-system-x86_64 \
-drive if=pflash,format=raw,readonly=on,file=UEFI_Firmware/OVMF_CODE.fd \
-drive if=pflash,format=raw,file=UEFI_Firmware/OVMF_VARS.fd \
-drive if=ide,file=fat:rw:img,index=0,media=disk,format=raw -monitor stdio