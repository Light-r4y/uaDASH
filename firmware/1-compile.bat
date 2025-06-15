arduino-cli -j16 compile -b esp32:esp32:esp32s3:UploadSpeed=115200,FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi firmware.ino -v


rem arduino-cli -j16 compile -b esp32:esp32:esp32s3:FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi,EventsCore=0 --build-property "compiler.cpp.extra_flags=-DJC8048W550C -O2" firmware.ino --output-dir ./artifacts -v