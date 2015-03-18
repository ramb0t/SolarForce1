#include <SoftwareSerial.h>
//Method to Tx data from Arduino COM port ->RF remote->receive on COM4 on PC
#define BAUD 57600  //same as 3dR current config setting

//SoftwareSerial serialFromGPS(2,3) //Rx, Tx
//SoftwareSerial serialToRFLink(4,5) //Rx, Tx
SoftwareSerial serialTxTest(3,0); //Rx Tx (only want to Tx)
  char inByte;
char GPSin;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  serialTxTest.begin(BAUD);

}

void loop() {
  // put your main code here, to run repeatedly:
if(serialTxTest.available() > 0){
    inByte = serialTxTest.read();
    Serial.write(inByte);}
}
