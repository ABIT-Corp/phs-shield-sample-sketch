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
    Serial.println("[send any data to shutdown]");
    while(Serial.available() == 0);
    
    Serial.print("Shutdown ... ");
    if(a3gs.shutdown()==0){
      Serial.println("OK");
      Serial.println("Wait for shutdown ...");
      delay(2000UL);
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

