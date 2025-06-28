@echo off
.\esptool.exe --chip esp32s3 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode keep --flash_freq keep --flash_size keep 0x0 "./firmware.ino.bootloader.bin" 0x8000 "./firmware.ino.partitions.bin" 0x10000 "./firmware.ino.bin"
pause