// httpPost() sample sketch
#include <SoftwareSerial.h>
#include "a3gs.h"

const char *server = "httpbin.org"; 
const char *path = "post"; 
const char *head = "Accept: text/html\r\nContent-Length: 33";
int port = 80;
char res[70]; 
char body[40]; 
int len;

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("OK.");
    
    Serial.print("httpPOST() requesting ... ");
    len = sizeof(res);
    int temp = 256;
    sprintf(body, "key=ABCDEFGHIJKLMNOP&field1=%d.%d", temp/10, temp%10);

    if (a3gs.httpPOST(server, port, path, head, body, res, &len, false) == 0) {
      Serial.println("OK.");
      Serial.println();
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

