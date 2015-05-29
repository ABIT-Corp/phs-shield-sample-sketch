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

