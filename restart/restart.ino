// restart() sample sketch
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
    Serial.println("[send any data to continue]");
    while(Serial.available() == 0);
    
    Serial.print("Restart ... ");
    if(a3gs.restart()==0){
      Serial.println("OK");
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

