// put&get sample sketch

#include <SoftwareSerial.h>
#include "a3gs.h"

#define SECTOR 2
uint8_t data[] = {
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
};
uint8_t buffer[sizeof(data)];

void setup()
{
  Serial.begin(115200);
  delay(3000);    // Wait for start serial monitor
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("OK.");
    Serial.print("Write flash memory sector: ");
    Serial.println(SECTOR);

    if (a3gs.put(SECTOR, data, sizeof(data)) == a3gsSUCCESS) {
        // put() succeed
        Serial.println("Done.");
        Serial.println("Write data");
        for (int i = 0; i < (int)sizeof(data); i++) {
          if(i>0 && i%16==0){
            Serial.println("");
          }
          Serial.print(data[i], HEX);
          Serial.print(" ");
        }
        Serial.println("");
        
        Serial.println("Read data");
        int sz = a3gs.get(SECTOR, buffer, sizeof(buffer));
        if (sz > 0) {
            for (int i = 0; i < sz; i++) {
                if(i>0 && i%16==0){
                  Serial.println();
                }
                Serial.print(buffer[i], HEX);
                Serial.print(" ");
            }
            Serial.println();
            Serial.println("Done.");
        }else{
          Serial.println("Can't get data.");
        }
    }else{
      Serial.println("Can't put data.");
    }
  }else{
    Serial.println("Failed.");
  }
  Serial.println("End.");
  a3gs.end();
}

void loop()
{
}

