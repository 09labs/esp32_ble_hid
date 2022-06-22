
#include "ble_hid.h"

BleKeyboard bleKeyboard("Joopan", "devOwnn");

// RN42KeyReport structure defined at ble_hid.h header file
RN42KeyReport reportPacket;


uint8_t rxPacket[RPT_SIZE] = {0,};
int cnt = 0;
bool bStart = false;

void setup() {
  #if CONSOLE_DEBUG
    Serial.begin(115200);
    Serial.println("BLE is ready");
  #endif
  Serial2.begin(115200);
  pinMode(BLE_CONNECT_LED, OUTPUT);
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected())
    digitalWrite(BLE_CONNECT_LED, LOW);
  else
    digitalWrite(BLE_CONNECT_LED, HIGH);
  
  if(Serial2.available())
  {
    char r = Serial2.read();

    if(bStart)
    {
      if((r != IDF_START) && (cnt  == RPT_SIZE-1)){
        bool ret = false;
        
        rxPacket[cnt] = r;
        cnt++;
        
        ret = parseData();
        
        bStart = false;
        memset(rxPacket, 0, sizeof(RPT_SIZE));
        memset(&reportPacket, 0, sizeof(RN42KeyReport));
        cnt = 0;
      }
      else{
        rxPacket[cnt] = r;
        cnt++;
      }
    }
    else{
      if(r == IDF_START){
        bStart = true;
        rxPacket[cnt] = r;
        cnt++;
      }
    }
  }
}

bool parseData()
{
  if(rxPacket[0] == IDF_START && cnt == RPT_SIZE)
  {
    memcpy(&reportPacket, rxPacket, sizeof(uint8_t) * RPT_SIZE);
    #if CONSOLE_DEBUG
      Serial.print("RAW Data : ");
      for(int i = 0 ; i < RPT_SIZE ; i++)
      {
        Serial.print(rxPacket[i],HEX);
        Serial.print(" ");
      }
      Serial.println("");
    #endif
    if(bleKeyboard.isConnected()){
      bleKeyboard.sendReport(&reportPacket.keys);
    }
    else
      return false;
    return true;
  }
  else{
    return false;
  }
}