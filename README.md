# ESP32 for QMK Keyboard
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
# How to work
Let's see QMK Firmware bluetooth feature. [Link](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_bluetooth.md)  
As you can see in this document, you need to add bluetooth options on rules.mk file.  

```
BLUETOOTH_DRIVER = RN42
BLUETOOTH_ENABLE = yes
```
And you need to edit the \~rn42_send_keyboard\~~ function in [rn42.c](https://github.com/qmk/qmk_firmware/blob/master/drivers/bluetooth/rn42.c) as a below.  
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