// getVersion() sample sketch
#include <SoftwareSerial.h>
#include "a3gs.h"

#define INTERVAL  1000  // Blink interval

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("OK.");
  }else{
    Serial.println("Failed.");
  }
}

void loop()
{
  Serial.println("LED ON");
  a3gs.setLED(true);
  delay(INTERVAL);
  Serial.println("LED OFF");
  a3gs.setLED(false);
  delay(INTERVAL);
}

