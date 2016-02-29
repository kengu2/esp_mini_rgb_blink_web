/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
  replace the hostname with the one printed on serial
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

char* host = "esp8266";

const char* ssid = "VaasaHacklab-g";
const char* password = "xxxxxxxx";


//LDR = A0;
//RED = 15;
//GREEN = 12;
//BLUE = 13;
//BUTTON = 4;

#define greenPin 12
#define bluePin 13
#define redPin 15

int pin = 13;
int Red = 1;
int Green = 1;
int Blue = 1;


String content;


ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void handleRgb() {

  String Value = httpServer.arg("red");
  Red = Value.toInt();
  digitalWrite(redPin, Red);
  Value = httpServer.arg("green");
  Green = Value.toInt();
  digitalWrite(greenPin, Green);
  Value = httpServer.arg("blue");
  Blue = Value.toInt();
  digitalWrite(bluePin, Blue);


  content ="<!DOCTYPE HTML>\r\n<html>\
  <html>\
<body>\
<form method='get' action='rgb'>\
  <input type='checkbox' name='red' value='1' ";
    if (Red==1) content += "checked";
  content += "> Red<br>\
  <input type='checkbox' name='green' value='1' ";
  if (Green==1) content += "checked";
  content +="> Green<br>\
  <input type='checkbox' name='blue' value='1' ";
  if (Blue==1) content += "checked";
  content +="> Blue <br>\
  <input type='submit'>\
</form> \
</body>\
</html>";


  httpServer.send(200, "text/html", content);
}

void setRgb() {
  content = "<!DOCTYPE HTML>\r\n<html>";
  content += "bloo";
  String Value = httpServer.arg("red");
  Red = Value.toInt();
  digitalWrite(redPin, Red);
  Value = httpServer.arg("green");
  Green = Value.toInt();
  digitalWrite(greenPin, Green);
  Value = httpServer.arg("blue");
  Blue = Value.toInt();
  digitalWrite(bluePin, Blue);
  
  httpServer.send(200, "text/html", content);

}


void setup(void){

  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying.");
  }

  String MacAddress = WiFi.softAPmacAddress();
  String HostName = WiFi.hostname();
  //MacAddress.toCharArray(host, 20);
  HostName.toCharArray(host, 20);
  Serial.println(host);
  Serial.println(WiFi.localIP());
  pinMode(D0, OUTPUT);
  pinMode(A0, INPUT);


  pinMode(pin, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(15, OUTPUT);


  MDNS.begin(host);

  httpUpdater.setup(&httpServer);
  httpServer.begin();

  httpServer.on("/rgb", handleRgb);
  httpServer.on("/setrgb", setRgb);


  MDNS.addService("http", "tcp", 80);
  
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
}



// the loop function runs over and over again forever
void loop() {
  httpServer.handleClient();
  int light = map(analogRead(A0),100,1024,0,255);

//  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(15, HIGH);   // turn the LED on (HIGH is the voltage level)
//  analogWrite(15, light);
//  analogWrite(12, light);
//  analogWrite(pin, light);
//  Serial.println(".");
  Serial.print(light);
//  delay(1000);              // wait for a second
//  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
//  digitalWrite(15, LOW);
  delay(1000);              // wait for a second
}
