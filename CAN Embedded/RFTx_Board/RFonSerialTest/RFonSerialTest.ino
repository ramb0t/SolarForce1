#include <SoftwareSerial.h>

#define BAUDRATE 57600

SoftwareSerial radioSerial(0,1); // Rx, Tx
char inByte;

void setup(){
  Serial.begin(BAUDRATE);
  radioSerial.begin(BAUDRATE);
}

void loop(){
  if(radioSerial.available() > 0){
    inByte = radioSerial.read();
    Serial.write(inByte);
  }
}
