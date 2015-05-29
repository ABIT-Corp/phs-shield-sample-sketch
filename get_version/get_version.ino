// getVersion() sample sketch
#include <SoftwareSerial.h>
#include "a3gs.h"
char temp[32];

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("OK.");
    if (a3gs.getVersion(temp) == 0) {
        Serial.print("Version: ");
        Serial.println(temp);
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

