# dash5_esp32s3

rusEFI lowcost CAN-bus dashboard
-------------------------------------------------------------------

The device can display engine operating parameters and bench test coils and injectors (under development).

The project can work on GUITION JC8048W550C display board and Waveshare ESP32-S3-Touch-LCD-7 (you can add more =))

For change brightness use swipe up/down (only 5inch GUITION JC8048W550C).

Change main/bench screen use swipe left/right.

Main screen:

![dashboard](https://github.com/Light-r4y/dash5_esp32s3/blob/main/media/main_screen.png)

Bench test screen:

![dashboard](https://github.com/Light-r4y/dash5_esp32s3/blob/main/media/bench_screen.png)

-------------------------------------------------------------------

## Build with Arduino CLI

```
arduino-cli core update-index
arduino-cli lib install lvgl@8.4.0
arduino-cli lib install LovyanGFX@1.2.0
arduino-cli lib install ESP32_IO_Expander@1.1.0
arduino-cli core install esp32:esp32
arduino-cli -j16 compile -b esp32:esp32:esp32s3:FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi,EventsCore=0 --build-property "compiler.cpp.extra_flags=-D<set-you-dislay> -O2" firmware.ino --output-dir ./artifacts -v
arduino-cli upload -b esp32:esp32:esp32s3:FlashSize=16M,PartitionScheme=app3M_fat9M_16MB,PSRAM=opi,EventsCore=0 --build-path ./artifacts -p <you-display-COMport> -v
```

-------------------------------------------------------------------

## Flash for use ESP Web flasher
https://espressif.github.io/esptool-js/

1. Press "Connect"
2. Select you connected display COM port (maybe can use boot button on board, for into bootloader mode)
3. Press "Erase flash" (optional)
4. Set flash address 0x0 -> add file "firmware.ino.bootloader.bin"
5. Set flash address 0x8000 -> add file "firmware.ino.partitions.bin"
6. Set flash address 0x10000 -> add file "firmware.ino.bin"
7. Press "Program"
8. Wait and watch carefully as the inscriptions appear on the black screen.
9. If you watch "Hard resetting via RTS pin...", press RST button on board and be happy! Else sad and try repeat or check you binary files.



![dashboard](https://github.com/Light-r4y/dash5_esp32s3/blob/main/media/esp-flasher.png)

-------------------------------------------------------------------

## Build settings if use Arduino IDE

(maybe for best performance compile with -O2/O3 flag)

Required library:

- LVGL v8 (graphic lib)

- LovyanGFX (display driver)

- ESP32_IO_Expander@1.1.0 (if use Waveshare board)

![build_settings](https://github.com/Light-r4y/dash5_esp32s3/blob/main/media/adruino_settings.jpg)

-------------------------------------------------------------------
## Hardware assembly example
-------------------------------------------------------------------

Display devboard: GUITION JC8048W550C

CAN tranceiver: TJA1050

Power module: MP1584

Screw : DIN 912 M3x16

Heat brass insert nut: M3x5x5

-------------------------------------------------------------------

Connectors:

Adapter -- ECU wiring (JST XH 2.54 4pin)

GND / 12V / CAN_L / CAN_H

-------------------------------------------------------------------

P1 Power

(use 4pin JST1.25 connector near the USB)

Power module MP1584 Vout -- 5V

RX/TX unused

Power module MP1584 GND -- GND

-------------------------------------------------------------------

P4 CANbus 

Adapter -- Display devboard (4pin JST1.25)

CAN tranceiver VCC -- 3.3V !!! Note: sometimes not working, use 5V form another place

CAN tranceiver GND -- GND

CAN tranceiver TX -- PIN_17

CAN tranceiver RX -- PIN_18

-------------------------------------------------------------------

![assembled1](https://github.com/Light-r4y/dash5_esp32s3/blob/main/media/7.png)


![assembled2](https://github.com/Light-r4y/dash5_esp32s3/blob/main/media/8.png)


![assembled3](https://github.com/Light-r4y/dash5_esp32s3/blob/main/media/6.jpeg)
