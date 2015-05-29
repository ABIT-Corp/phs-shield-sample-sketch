// httpGet() sample sketch
#include <SoftwareSerial.h>
#include "a3gs.h"

#if 1
const char *server = "www.example.com";
const char *path = "index.html";
#else
const char *server = "httpbin.org"; 
const char *path = "get"; 
#endif
const char *head = "Accept: text/html\r\nConnection: Keep-Alive";
int port = 80;

char res[a3gsMAX_RESULT_LENGTH];
int len;

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("OK.");
    
    modem_mode_change(0);
    Serial.println();
    int rssi;
    if (a3gs.getRSSI(rssi) == 0) {
      Serial.print("RSSI: ");
      Serial.println(rssi);
    }
    Serial.println();
    modem_mode_change(1);
    
    Serial.println();
    Serial.print("httpGET() requesting ... ");
    len = sizeof(res);
    if (a3gs.httpGET(server, port, path, res, len, 0, head) == 0) {
      Serial.println("OK.");
      Serial.print(res);
      Serial.println();
      delay(3000);
      a3gs.disconnectTCP();
    }else {
      Serial.print("Can't get HTTP response from ");
      Serial.println(server);
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
