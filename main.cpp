#include <Arduino.h>

int triggerPort = 7;
int echoPort = 8;

void setup(){
  pinMode(triggerPort,OUTPUT);
  pinMode(echoPort, INPUT);
  Serial.begin(115200);
  
}
void loop(){
  digitalWrite(triggerPort, LOW);
  digitalWrite(triggerPort, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPort,LOW);

  long duration = pulseIn(echoPort,HIGH);

  long r = 3.4*duration/2;
 
  float distance = r/100.00;

  Serial.print("distance ");

  Serial.println(distance);

  delay(100);

  if(distance>50){
      Serial.print("away");
  }
  
}
