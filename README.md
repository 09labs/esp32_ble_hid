# ESP32 for QMK Keyboard
This project allows you to make the ESP32 series as a BLE HID module for QMK Keyboard.  
Keep in mind that this project is only available in AVR based chips like `ATmega16u4, ATmegae32u4, ATmega328, ATmega32A and so on`.  
Refer to this document for a list of [compatible AVR microcontrollers](https://github.com/qmk/qmk_firmware/blob/master/docs/compatible_microcontrollers.md).  

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

This project was tested on ESP32-DevKitC, ESP32-S3-DevKitM-1, LOLIN D32 and LOLIN D32 PRO.  
As expected, This project support almost all ESP32 series Bluetooth modules.  
But, ESP32-S2 series and ESP8266 series cannot support bluetooth feature.  
### Do not use ESP32-S2 and ESP8266!!!

If you want to see readme in Korean, Click this [link](https://github.com/09labs/esp32_ble_hid/blob/bugfix/README_KR.md).

---
# How to work
Let's see QMK Firmware bluetooth feature. [Link](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_bluetooth.md)  
As you can see in this document, you need to add bluetooth options on rules.mk file.  
rules.mk file located in the keyboard project directory.  
`qmk_firmware/keyboards/foo/bar/rules.mk`

```
BLUETOOTH_DRIVER = RN42
BLUETOOTH_ENABLE = yes
```  
And you need to edit the `rn42_send_keyboard` function in [rn42.c](https://github.com/qmk/qmk_firmware/blob/master/drivers/bluetooth/rn42.c) as a below.  
```c
void rn42_send_keyboard(report_keyboard_t *report) {
    uart_write(0xFD);
    uart_write(0x09);
    uart_write(0x01);
    uart_write(report->mods);
    uart_write(0x00);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        uart_write(report->keys[i]);
    }
    // Added end flag
    uart_write(0xDF);
}
```  

### RN-42 `Raw Report Mode` format  
![RN42_Protocol](https://github.com/09labs/esp32_ble_hid/blob/bugfix/img/rn42_raw_report.png)

---

# Installation
* First, Make sure you can use the ESP32 series with the Arduino IDE.  
If you want to use ESP32 S3, add the url to the `Additional Board Manager URLs` at Arduino preferences.  
Preferences located at `Files -> Preferences`  
`https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json`  

* 2nd, In the Arduino IDE go to `Sketch -> Include Library -> Add .Zip Library"` and select the [ESP32-BLE-Keyboard.zip](https://github.com/T-vK/ESP32-BLE-Keyboard).  
* 3rd, In the Arduino IDE go to `Sketch -> Include Library -> Manage Library` and search `espsoftwareserial`.   
* 4th, Download the ZIP this project `Code -> Download ZIP`.  
* 5th, Unzip this project file and open `esp32_qmk/esp32_qmk.ino`.  
* 6th, Change software serial pin you want to use.
```c
#define SW_TX 22
#define SW_RX 23
```
* 7th, Compile arduino project and Upload the clode to your ESP32 board.  

# Thanks to...
T-vK`s [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) and plerup's [espsoftwareserial](https://github.com/plerup/espsoftwareserial) library was very helpful in developing this project.  
