/*

 Arduino --> ThingSpeak Channel via Ethernet
 
 The ThingSpeak Client sketch is designed for the Arduino and Ethernet.
 This sketch updates a channel feed with an analog input reading via the
 ThingSpeak API (https://thingspeak.com/docs)
 using HTTP POST. The Arduino uses DHCP and DNS for a simpler network setup.
 The sketch also includes a Watchdog / Reset function to make sure the
 Arduino stays connected and/or regains connectivity after a network outage.
 Use the Serial Monitor on the Arduino IDE to see verbose network feedback
 and ThingSpeak connectivity status.
 
 Getting Started with ThingSpeak:
 
 * Sign Up for New User Account - https://thingspeak.com/users/new
 * Create a new Channel by selecting Channels and then Create New Channel
 * Enter the Write API Key in this sketch under "ThingSpeak Settings"
 
 Arduino Requirements:
 
 * Arduino with Ethernet Shield or Arduino Ethernet
 * Arduino 1.0+ IDE
 
 Network Requirements:
 
 * PHS Shield    
 * DHCP enabled on Router
 * Unique MAC Address for Arduino
 
 Created: October 17, 2011 by Hans Scharler (http://www.iamshadowlord.com)
 
 Additional Credits:
 Example sketches from Arduino team, Ethernet by Adrian McEwen
 */

#include <SoftwareSerial.h>
#include "a3gs.h"

#define ServerAddress               "api.thingspeak.com"
#define WriteAPIKey                 "XXXXXXXXXXXXXXXX"
#define LM61BIZ_Pin                 A1          // LM61BIZ 
#define Lux_Pin                     A4          // S9648-100 
#define Motion                      8           // PIR Sensor (#555-28027)
#define UpdateInterval             (60000UL)    // Time interval in milliseconds to update ThingSpeak

// Variable Setup
unsigned long lastTime = 0; 
uint8_t res[40];
char data[40]; 
char body[30]; 
int count = 0;
int mot = 0;

void setup()
{
  pinMode(14, OUTPUT); // A0(LM61BIZ - GND)
  digitalWrite(14, LOW);
  pinMode(16, OUTPUT); // A2(LM61BIZ - VSS+)
  digitalWrite(16, HIGH);
  pinMode(17, OUTPUT); // A3(S9648 - GND)
  digitalWrite(17, LOW);
  pinMode(19, OUTPUT); // A5(S9648 - VSS+)
  digitalWrite(19, HIGH);

  // Start Serial for debugging on the Serial Monitor
  Serial.begin(115200); 
  delay(3000); // Wait for Start Serial Monitor 
  Serial.println(">Ready."); 

  // Start PHS on Arduino
  startPHS();
}

void loop()
{
  // Update ThingSpeak
  if((millis() - lastTime > UpdateInterval))
  {
    // Read value from analog input pin
    int temp = getTemp();
    int lx   = getIlluminance();

    sprintf(data, "field1=%d.%d&field2=%d&field3=%d", temp/10, temp%10, lx, mot);
    Serial.print(">PUT: ");
    Serial.print(count++, DEC);
    Serial.print(", ");
    Serial.println(data);        
    updateThingSpeak(data);
    
    mot = 0;
  }
  
  delay(1000);
  if(getMotion()){
    mot++;
  }
}

void updateThingSpeak(char * data)
{
  Serial.print("Connecting to ThingSpeak ... ");

  if (a3gs.connectTCP(ServerAddress, 80)==0)
  { 
    int field_size;
    Serial.println("OK."); 

    sprintf(body, "key=%s&", WriteAPIKey);
    field_size = strlen(body) + strlen(data);

    a3gs.write("POST /update HTTP/1.1\r\n");
    sprintf((char *)res, "Host: %s\r\n", ServerAddress);
    a3gs.write((char *)res);
    a3gs.write("Content-Type: application/x-www-form-urlencoded\r\n");
    sprintf((char *)res, "Content-Length: %d\r\n\r\n", field_size);
    a3gs.write((char *)res);
    a3gs.write(body);
    a3gs.write(data);

    while(1){
      char c = a3gs.read(res, 32);
      if(c>0){
        res[(uint8_t)c] = 0;
        Serial.print((char *)res);
      }else{
        break;
      }
    }
    a3gs.disconnectTCP();
    Serial.println("disconnected");
  }
  lastTime = millis(); 
}


void startPHS()
{
  Serial.print("Initializing.. "); 
  if (a3gs.start() == 0 && a3gs.begin() == 0){ 
    Serial.println("OK."); 
  }else { 
    Serial.println("Failed."); 
    while (1) ;  // STOP 
  } 
}


int getTemp(void) 
{ 
  int adjust = -0;
  int mV = analogRead(LM61BIZ_Pin) * 4.88; 
  return (mV - 600 + adjust);   
} 

int getIlluminance(void)
{
  int mV = analogRead(Lux_Pin) * 4.88;
  return ((mV * 100.0) / 290.0);
}

int getMotion(void) 
{ 
  int sensor = digitalRead(Motion); 
  return (sensor);   
} 


