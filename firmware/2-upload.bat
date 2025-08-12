@echo off
..\release\esptool.exe --chip esp32s3 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode keep --flash_freq keep --flash_size keep 0x0 "./artifacts/firmware.ino.bootloader.bin" 0x8000 "./artifacts/firmware.ino.partitions.bin" 0xe000 "../release/boot_app0.bin" 0x10000 "./artifacts/firmware.ino.bin"

pause


rem arduino-cli upload -b esp32:esp32:esp32s3:UploadSpeed=115200,FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi firmware.ino -v -p com16


rem arduino-cli upload -b esp32:esp32:esp32s3:FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi,EventsCore=0 --build-path ./artifacts -p COM6 -v