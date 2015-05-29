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


void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("OK.");
    
    Serial.print("httpGET() requesting ... ");
    if (a3gs.connectTCP(server, 80)==0){ 
      Serial.println("OK.");
      sprintf(res, "GET /%s HTTP/1.1\r\n", path);
      a3gs.write(res);
      sprintf(res, "Host: %s\r\n", server);
      a3gs.write(res);
      a3gs.write("Accept: text/html\r\n");
      a3gs.write("Connection: Keep-Alive\r\n\r\n");
      while(1){
        char c = a3gs.read((uint8_t *)res, 32);
        if(c>0){
          res[(uint8_t)c] = '\0';
          Serial.print(res);
        }else{
          break;
        }
      }
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

