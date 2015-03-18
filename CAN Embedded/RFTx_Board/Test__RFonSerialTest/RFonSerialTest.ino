#include <SoftwareSerial.h>

#define BAUDRATE 57600

SoftwareSerial radioSerial(4,3); // Rx, Tx
SoftwareSerial gpsSerial(2,8); //Rx Tx
char inByteRec;
char inGPS;
int inByte;

void setup(){
  Serial.begin(BAUDRATE);          //h/w serial 0/1
  radioSerial.begin(BAUDRATE);    //serial to radio O/P
  gpsSerial.begin(BAUDRATE);      //serial for GPS
}

void loop(){
  radioSerial.listen();
  if(radioSerial.available() > 0){
    inByteRec = radioSerial.read();
    Serial.print(F("Incoming from Follow Car: \n"));
    radioSerial.write(inByteRec);
    delay(300);
  }
  
  gpsSerial.listen();
  Serial.print("GPS data incoming\n");
  if(gpsSerial.available()>0){
    inGPS = gpsSerial.read();
    delay(300);
    inByte = 63;
    Serial.print(F("Sent to Follow Car : "));
    Serial.print(inGPS);
    radioSerial.write(inGPS);
    delay(20);
  }
  
}
