arduino-cli -j16 compile -b esp32:esp32:esp32s3:UploadSpeed=115200,FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi firmware.ino -v


rem arduino-cli -j16 compile -b esp32:esp32:esp32s3:FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi,EventsCore=0 --build-property "build.defines=-DBOARD_HAS_PSRAM -D<display_define>" --build-property compiler.optimization_flags=-O2 firmware.ino --output-dir ./artifacts -v