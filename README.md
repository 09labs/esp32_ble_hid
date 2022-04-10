# esp32_ble_hid
This project allows you to make the ESP32 series as a BLE HID module for QMK Keyboard.
Currently, QMK Firmware only supports two bluetooth module: RN-42 and Adafruit Feather 32u4 Bluefruit LE.
Not supported yet, but possible bluetooth module list:

* Bluefruit LE UART Friend
* HC-05 boards flashed with RN-42 firmware [Link](http://pastebin.com/V91PZBnJ)
* Sparkfurn Bluetooth Mate
* HM-13 based boards

RN-42 Bluetooth module uses UART as communication method.
Adafruit Feather 32u4 Bluefruit LE module uses SPI as communication method.

The RAW report mode of the RN-42 module uses a very simple protocol.
So I modified the source code to make ESP32 series work like RN-42 module.
---
이 프로젝트는 ESP32 시리즈를 QMK 펌웨어를 사용하는 키보드용 BLE HID 모듈로 제작할 수 있습니다.
현재 QMK 펌웨어는 RN-42와 Adafruit Feather 32u4 Bluefruit LE 두 가지 블루투스 모듈만 지원합니다.

아직 지원하지 않지만 