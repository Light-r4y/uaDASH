@echo off
.\esptool.exe --chip esp32s3 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode keep --flash_freq keep --flash_size keep 0x0 "esp32.esp32.esp32s3/firmware.ino.bootloader.bin" 0x8000 "esp32.esp32.esp32s3/firmware.ino.partitions.bin" 0x10000 "esp32.esp32.esp32s3/firmware.ino.bin"
pause