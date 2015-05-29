// getLocation() sample sketch
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
    
    modem_mode_change(0);
      
    if (a3gs.getLocation(a3gsMPSTANDALONE, temp2, temp1) == 0) {
      Serial.print("latitude: ");
      Serial.println(temp2);
      Serial.print("longitude: ");
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

void modem_mode_change(int ppp_on)
{
  int profile;
  unsigned int ppp_mode;
  
  if(ppp_on){
    ppp_mode = 5;
  }else{
    ppp_mode = 6;
  }
  a3gs.getDefaultProfile(&profile);
  Serial.print("profile: 0x");
  Serial.println(profile, HEX);
  if((profile&0xff00)>>8 != ppp_mode){
    a3gs.setDefaultProfile(profile);
    if(ppp_on){
      a3gs.setDefaultProfile(1);
      Serial.println("wait until ppp link up");
    }else{
      a3gs.setDefaultProfile(3);
      Serial.println("wait until ppp link down");
    }
    while(1){
      delay(10000);
      a3gs.getDefaultProfile(&profile);
      Serial.print("profile: 0x");
      Serial.println(profile, HEX);
      if((profile&0xff00)>>8 == ppp_mode){
        Serial.println("ppp link status changed");
        break;
      }
    }
  }
}
