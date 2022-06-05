#ifndef BLE_HID_H
#define BLE_HID_H

#include <BleKeyboard.h>

#define CONSOLE_DEBUG 0
#define BLE_CONNECT_LED 15
#define RPT_SIZE 11

// Start flag
#define IDF_START 0xFD

/** This structure based on rn-42 module
 *  RAW report mode data protocol
 *  [0] - Start flag
 *  [1] - Packet length (include descriptor)
 *  [2] - Descriptor
 *  [3-10] - Data field
 */
 
typedef struct
{
  uint8_t start;
  uint8_t len;
  uint8_t desc;
  KeyReport keys;
} RN42KeyReport;

#endif