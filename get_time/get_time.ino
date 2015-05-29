// getTime() sample sketch
#include <SoftwareSerial.h>
#include "a3gs.h"
char temp1[32];
char temp2[32];
void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("OK.");
    if (a3gs.getTime(temp2, temp1) == 0) {
      Serial.print("date: ");
      Serial.println(temp2);
      Serial.print("time: ");
      Serial.println(temp1);
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

