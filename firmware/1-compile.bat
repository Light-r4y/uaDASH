rem You can select dispaly board build options: JC8048W550C, WAVESHARE_S3_LCD5, WAVESHARE_S3_LCD7, Sunton_S3_LCD7

arduino-cli -j16 compile -b esp32:esp32:esp32s3:FlashSize=8M,PartitionScheme=huge_app,PSRAM=opi --build-property "build.defines=-DBOARD_HAS_PSRAM -DWAVESHARE_S3_LCD7" --build-property compiler.optimization_flags=-Os firmware.ino --output-dir ./artifacts -v

rem arduino-cli -j16 compile -b esp32:esp32:esp32s3:UploadSpeed=115200,FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi firmware.ino -v


rem arduino-cli -j16 compile -b esp32:esp32:esp32s3:FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi,EventsCore=0 --build-property "build.defines=-DBOARD_HAS_PSRAM -D<display_define>" --build-property compiler.optimization_flags=-O2 firmware.ino --output-dir ./artifacts -v