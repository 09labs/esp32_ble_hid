#ifndef BLE_HID_H
#define BLE_HID_H

#include <BleKeyboard.h>

#define CONSOLE_DEBUG 0
#define RPT_SIZE 12

// Start flag
#define IDF_START 0xFD

// End flag
#define IDF_END 0xDF

/** This structure based on rn-42 module
 *  RAW report mode data protocol
 *  [0] - Start flag
 *  [1] - Packet length (include descriptor)
 *  [2] - Descriptor
 *  [3-10] - Data field
 *  [11] - End flag 
 */
 
typedef struct
{
  uint8_t start;
  uint8_t len;
  uint8_t desc;
  KeyReport keys;
  uint8_t ends;
} RN42KeyReport;

#endif
