# dash5_esp32s3
rusEFI 5inch display dashboard 

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

CAN tranceiver VCC -- 3.3V

CAN tranceiver GND -- GND

CAN tranceiver TX -- PIN_17

CAN tranceiver RX -- PIN_18

-------------------------------------------------------------------

Build settings Arduino IDE

(maybe for best performance compile with -O2/O3 flag)

Required library:

- LVGL v8 (graphic lib)

- LovyanGFX (display driver)

![build_settings](https://github.com/Light-r4y/dash5_esp32s3/blob/main/img/adruino_settings.jpg)

-------------------------------------------------------------------

Dashboard interface:

![dashboard](https://github.com/Light-r4y/dash5_esp32s3/blob/main/img/4.png)


![assembled1](https://github.com/Light-r4y/dash5_esp32s3/blob/main/img/7.png)


![assembled2](https://github.com/Light-r4y/dash5_esp32s3/blob/main/img/8.png)


![assembled3](https://github.com/Light-r4y/dash5_esp32s3/blob/main/img/6.jpeg)


-------------------------------------------------------------------
-------------------------------------------------------------------

Case 3D printed (PETG)

![case_plane1](https://github.com/Light-r4y/dash5_esp32s3/blob/main/img/1.png)

![case_plane2](https://github.com/Light-r4y/dash5_esp32s3/blob/main/img/2.png)

![case_plane3](https://github.com/Light-r4y/dash5_esp32s3/blob/main/img/3.png)

