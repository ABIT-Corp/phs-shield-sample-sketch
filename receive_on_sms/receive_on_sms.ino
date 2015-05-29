// sendSMS() sample sketch

#include <SoftwareSerial.h>
#include "a3gs.h"

const int ledPin = 13;
volatile boolean received = false;
char msg[a3gsMAX_SMS_LENGTH+1], msn[a3gsMAX_MSN_LENGTH+1];
int number = 0;

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Ready.");

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED off

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("OK.");
    a3gs.onSMSReceived(ledOn);
    modem_mode_change(0);
    
    Serial.println("Ready to receive SMS(PHS Light Mail).");
  }else{
    Serial.println("Failed.");
  }
  Serial.println("Waiting mail ...");
}

void loop()
{
  if (received) {
    Serial.println("SMS is received.");
    if (a3gs.readSMS(msg, sizeof(msg), msn, sizeof(msn)) == 0) {
      Serial.print("MSN: ");
      Serial.println(msn);
      Serial.print("SMS: ");
      Serial.println(msg);
    }
    digitalWrite(ledPin, LOW);  // LED off
    received = false;
    a3gs.onSMSReceived(ledOn);  // Re-set handler
  }
}

void ledOn(void)
{
  digitalWrite(ledPin, HIGH);  // LED on
  received = true;
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
