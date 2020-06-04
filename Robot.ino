#include <ESP8266WiFi.h> 
#define EN1 D6 // Enable PIN to control speed 
#define EN2 D7 
const char* ssid = "rpi26"; 
const char* password = "FP380000"; 
WiFiClient client; 
WiFiServer server(80); 
String data = ""; 
int LS=0; 
int RS=0; 
void setup() { 
Serial.begin(115200); 
pinMode(EN1, OUTPUT); 
pinMode(EN2,OUTPUT); 
// Connect to WiFi network 
Serial.print("Connecting to "); 
Serial.println(ssid); 
WiFi.begin(ssid, password); 
while (WiFi.status() != WL_CONNECTED) { 
delay(500); 
Serial.print("."); 
} 
Serial.println("WiFi connected"); 
// Start the server 
server.begin(); 
Serial.println("Server started"); 
// Print the IP address 
Serial.print("Use this URL to connect: "); 
Serial.print("http://"); 
Serial.print(WiFi.localIP()); 
Serial.println("/"); 
} String checkClient (void) 
{ 
while (!client.available()) 
delay(1); 
String request = client.readStringUntil('\r'); 
Serial.println(request); 
client.flush(); 
return request; 
} void loop() { 
client = server.available(); 
if (!client) { 
return; 
} 
data = checkClient (); 
if(data.indexOf('L')!=-1) 
LS=(data.substring(data.indexOf('L')+1,data.indexOf('&'))).toInt(); 
if(data.indexOf('R')!=-1) 
RS=(data.substring(data.indexOf('R')+1,data.indexOf('&'))).toInt(); 
LS=LS-(LS%100); 
RS=RS-(RS%100); 
analogWrite(EN1,LS); 
analogWrite(EN2,RS); 
Serial.println(RS); 
Serial.println(data); 
client.println("HTTP/1.1 200 OK"); 
delay(1); 
data=""; 
} 
