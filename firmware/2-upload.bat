arduino-cli upload -b esp32:esp32:esp32s3:UploadSpeed=115200,FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi firmware.ino -v -p com16


rem arduino-cli upload -b esp32:esp32:esp32s3:FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi,EventsCore=0 --build-path ./artifacts -p COM6 -v