#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
#define BAUDRATE 9600
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(2,8); //need to Rx only
SoftwareSerial radioSerial(RXPin, TXPin); //to send serial RF

void setup()
{
  Serial.begin(BAUDRATE);
  ss.begin(GPSBaud);
  radioSerial.begin(BAUDRATE);
  
  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}

void loop()
{
      radioSerial.listen();        //listen on RF link
      //checkIncoming();            //any messages from follwocar?
  // This sketch displays information every time a new sentence is correctly encoded.
      ss.listen();
  while (ss.available() > 0)
    
    if (gps.encode(ss.read()))
      sendToFollowCar();
      

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
} 


void sendToFollowCar()
{
  Serial.print(F("Location: "));
  serialOnRF(gps, radioSerial); 
 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour()+2); //for GMT+2 adjust as needed
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

void serialOnRF(TinyGPSPlus gpsobj, SoftwareSerial srlobj)
{
  srlobj.listen(); //switch to outgoing follow car port
  
  srlobj.print("---------------------------------------");
  srlobj.print("\nThis packet is from the Solar Car\n "); 
  srlobj.print("Location: ");
  
  if (gpsobj.location.isValid())
  {
    srlobj.print(gpsobj.location.lat(), 6);
    srlobj.print(F(","));
    srlobj.print(gpsobj.location.lng(), 6);
  }
  else
  {
    srlobj.print(F("INVALID"));
  }
  
  srlobj.print(F("  Date: "));
  if (gps.date.isValid())
  {
    srlobj.print(gps.date.month());
    srlobj.print(F("/"));
    srlobj.print(gps.date.day());
    srlobj.print(F("/"));
    srlobj.print(gps.date.year());
  }
  else
  {
    srlobj.print(F("INVALID"));
  }
  
  if (gps.time.isValid())
  {
    srlobj.print(F("  Time: "));
    if (gps.time.hour() < 10) srlobj.print(F("0"));
    srlobj.print(gps.time.hour());
    srlobj.print(F(":"));
    if (gps.time.minute() < 10) srlobj.print(F("0"));
    srlobj.print(gps.time.minute());
    srlobj.print(F(":"));
    if (gps.time.second() < 10) srlobj.print(F("0"));
    srlobj.print(gps.time.second());
    srlobj.print(F("."));
    if (gps.time.centisecond() < 10) srlobj.print(F("0"));
    srlobj.print(gps.time.centisecond());
  }
  else
  {
    srlobj.print(F("INVALID"));
  }
  
  srlobj.print("\n---------------------------------------\n");
   delay(100);
  ss.listen();
 
}

void checkIncoming()
{
  radioSerial.listen();
    if ( radioSerial.available()){
    int asciiint; 
    while (radioSerial.available()>0)
    {
      asciiint = radioSerial.read();
      radioSerial.write(asciiint);
      Serial.write(asciiint);
//inByte = radioSerial.readBytes();
    }
     // radioSerial.println(inByte);
     // Serial.println(inByte);
      //inByte = ""; //reset
      radioSerial.print("This packet is from the Follow Car\n ");      
  
     radioSerial.print("\n*******Sent to Solar Car OK*********\n");
     Serial.print("\n*******Transmission Incoming*********\n");
     Serial.print("Contents: \n");
     Serial.print(asciiint);
     ss.listen();
  }
}
