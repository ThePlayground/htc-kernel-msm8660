echo "making ramdisk"
./mkbootfs boot.img-ramdisk | gzip > newramdisk.cpio.gz
./mkbootimg --cmdline 'console=ttyHSL0 androidboot.hardware=shooter no_console_suspend=1' --kernel zImage --ramdisk newramdisk.cpio.gz -o boot.img --base 0x48000000
