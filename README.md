# ESP32 for QMK Keyboard
This project allows you to make the ESP32 series as a BLE HID module for QMK Keyboard.  
Keep in mind that this project is only available in AVR based chips like `ATmega16u4, ATmegae32u4, ATmega328, ATmega32A` and so on.  
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

This project was tested on `ESP32-DevKitC, ESP32-S3-DevKitM-1, LOLIN D32 and LOLIN D32 PRO`.  
As expected, This project support almost all ESP32 series Bluetooth modules.  
But, ESP32-S2 series and ESP8266 series cannot support bluetooth feature.  
### Do not use ESP32-S2 and ESP8266!!!

If you want to see readme in Korean, Click this [link](https://github.com/09labs/esp32_ble_hid/blob/bugfix/README_KR.md).

---
# How to work  

### QMK <-> RN-42 Communication structure
![comm_structure](https://github.com/09labs/esp32_ble_hid/blob/bugfix/img/comm_structure.png)  
### RN-42 `Raw Report Mode` format  
![RN42_Protocol](https://github.com/09labs/esp32_ble_hid/blob/bugfix/img/rn42_raw_report.png)

This is structure for commuication between QMK Keyboard and RN-42 bluetooth module.  
To enable bluetooth communication, let's see QMK Firmware bluetooth feature. [Link](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_bluetooth.md)  
As you can see in this document, you need to add bluetooth options on rules.mk file.  
rules.mk file located in the keyboard project directory.  
`qmk_firmware/keyboards/foo/bar/rules.mk`

```
BLUETOOTH_DRIVER = RN42
BLUETOOTH_ENABLE = yes
```  

Unfortunately, You cannot use ESP32 module with original QMK Firmware.  
Because ESP32 module doesn't have RN-42 protocol and i tried to build the ESP32 firmware to work like the RN-42.  
But it doesn't work well, so i modified the RN-42 protocol a bit.  

### Modified Raw Report Mode format
![ESP32_Protocol](https://github.com/09labs/esp32_ble_hid/blob/bugfix/img/mod_raw_report.png)

you need to edit the `rn42_send_keyboard` function in [rn42.c](https://github.com/qmk/qmk_firmware/blob/master/drivers/bluetooth/rn42.c) as a below.  
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

---

# Installation
If you have modified the rn42.c file, you are ready to use the bluetooth feature with the ESP32.  
Now, after uploading the firmware to the ESP32 and wiring it, you can use your keyboard wirelessly.  

### Upload the code
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
* 7th, Compile arduino project and upload the code to your ESP32 board.  

### Wiring

![wiring](https://github.com/09labs/esp32_ble_hid/blob/bugfix/img/esp32_avr_wiring.png)  
If you don't use the ESP32 DevKit (ESP32, ESP32-S3 anything), refer to the block diagram above.
1st, the usb D+, D- pin will be connected switch selector. The reason that you need to use the switch selector is to upload the code to ESP32.  
2nd, If you use the ESP32 DevKit, you just connect Tx, Rx pin between AVR Microcontroller and ESP DevKit. 
3rd, 

# Thanks to...
T-vK`s [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) and plerup's [espsoftwareserial](https://github.com/plerup/espsoftwareserial) library was very helpful in developing this project.  
