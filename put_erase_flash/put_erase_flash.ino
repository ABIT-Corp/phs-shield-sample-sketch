// put/get sample sketch

#include <SoftwareSerial.h>
#include "a3gs.h"

#define SECTOR 0
uint8_t data[] = {
    'E', 'R', 'A', 'S', 'E',
};
uint8_t buffer[sizeof(data)];

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("OK.");

    Serial.println("Flash memory");
    if (a3gs.put(SECTOR, data, sizeof(data)) == a3gsSUCCESS) {
      Serial.println("All sectors is erased.");
    }else{
      Serial.println("Can't erase.");
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
