// sendSMS() sample sketch

#include <SoftwareSerial.h>
#include "a3gs.h"

char *msn = "070XXXXXXXX";         // Replace your phone number!
char *msg = "TEST MESSAGE. HELLO!";// ASCII Stringchar 

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("OK.");
    
    modem_mode_change(0);
    
    Serial.print("SMS sending.. ");
    if (a3gs.sendSMS(msn, msg, a3gsCS_ASCII) == 0){
      Serial.println("OK!");
    }else{
      Serial.println("Can't send SMS.");
    }
  }else{
    Serial.println("Failed.");
  }
  Serial.println("End.");
  a3gs.end();
}

void modem_mode_change(int ppp_on)
{
  int profile;
  int ppp_mode;
  
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

void loop()
{
}
