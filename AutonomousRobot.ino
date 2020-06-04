#include <ESP8266WiFi.h>
#define EN1 D6 // Enable PIN to control speed
#define EN2 D7
int x=0;
long duration=0;
 int trigP = D1; //D4
int echoP = D2; //D3

int LS=0;
int RS=0;
void setup() {
 Serial.begin(115200);
 pinMode(EN1, OUTPUT);
 pinMode(EN2,OUTPUT);
 pinMode(trigP, OUTPUT); // Sets the trigPin as an Output
pinMode(echoP, INPUT);
 

}

void loop() {
 digitalWrite(trigP, LOW); // Makes trigPin low
delayMicroseconds(2); // 2 micro second delay
digitalWrite(trigP, HIGH); // tigPin high
delayMicroseconds(10); // trigPin high for 10 micro
digitalWrite(trigP, LOW);
duration = pulseIn(echoP, HIGH); //Read echo pin, time in

x= duration*0.034/2;

if(x>100)
{
  LS=1000;
  RS=1000;
}
else
 {
LS= 1.64297009+0.25565121*x +0.79783941*x*x +100;//w0,w1,w2 for left
RS= 5.69131579+0.93955232*x -0.06617865*x*x +100;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ;//w0,w1,w2 for right
 }
 LS=LS-(LS%100);
 RS=RS-(RS%100);
 Serial.println(LS);
 analogWrite(EN1,LS);
 analogWrite(EN2,RS);
 
 }
