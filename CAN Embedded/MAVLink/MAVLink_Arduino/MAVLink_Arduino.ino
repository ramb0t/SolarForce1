#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "C:\Users\Matt\Documents\Arduino\libraries\mavlink\include\solarCarFINAL\solarCar\mavlink.h" 
#define MAVLINK_USE_CONVENIENCE_FUNCTIONS
#define BAUDRATE 9600

static const int RXPin = 4, TXPin = 3;
SoftwareSerial radioSerial(RXPin, TXPin); //to send serial RF
SoftwareSerial ss(2,8); //need to Rx only
TinyGPSPlus gps;
int counter;

//MAVLINK GLobal defs

const char *latitude;

const char *longitude;
const char *time;
const char *date;
const char *lock_error;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radioSerial.begin(BAUDRATE);
  ss.begin(9600);
  Serial.println(F("Setup starting"));
  
  mavlink_system_t mavlink_system;
}

void loop() {
  // put your main code here, to run repeatedly:

      
    Serial.println("(Solar Car Diag Console) Sending packet values: "); 
    
      /*MAVLINK asks to set all systm statuses as integers. For human readibility ENUMS are used in the appropriate headers
  these enums convert text for states to integers sent & interpreted. 3 phases to a message:
  --define the enum types you'll need and use friendly names e.g. value_name = MAV_ENUM_VALUE_NAME
  --use a send / encode function from the relevant header to send HEARTBEAT to get QGC/APM working
  --then have a function (see solarCar.h and the entire message_definitions folder for types to send
  --pass the values or enum friendly names to the functions
  --this ensures the message goes to MAVLink frame
  --connect to QGC and observe output! */
  
  
	// Define the system type (see solarCar.h for list of possible types) 
	int system_type = MAV_TYPE_GROUND_ROVER;
	int autopilot_type = MAV_AUTOPILOT_GENERIC;
        int base_mode = MAV_MODE_FLAG_AUTO_ENABLED;
	int custom_mode = MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
        int system_status = MAV_STATE_ACTIVE;
        
        
	// Initialize the required buffers
	mavlink_message_t msg; 
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
        uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
        
        
	// Pack the message
	// mavlink_message_heartbeat_pack(system id, component id, message container, system type, MAV_AUTOPILOT_GENERIC)
	mavlink_msg_heartbeat_pack(100, 200, &msg, system_type, autopilot_type,base_mode,custom_mode,system_status);
	radioSerial.write(buf,len);	
        //convenience function is msg_sys_status_pack for sending all status msgs
        //mavlink_msg_sys_status_pack( system_id, component_id, mavlink_message_t* msg, base_mode, nav_mode,status,vbat,motor_block, packet_drop)
        //randomly switches out system status values for show on QGC
        // Copy the message to send buffer 
//        delay(500);
//        mavlink_msg_hall_effect_pack(100, 200, &msg, 35, 0, 0);
//	radioSerial.write(buf,len);
        
        ss.listen();
        while (ss.available() > 0)
    
        if (gps.encode(ss.read()))
        {
          sendToFollowCar();
          mavlink_msg_gps_pack(100, 200, &msg, latitude, longitude, time, date, lock_error);
          uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	  radioSerial.write(buf,len);
        }
        

        delay(1000);
	// Send the message (.write sends as bytes) 
        Serial.println("Sending MAVLink Heartbeat Packet from Solar Car");
        radioSerial.write("Receiving MAVLink Heartbeat Packet from Solar Car");
        
}


void sendToFollowCar()
 {
   unsigned int i=0;
   double gpsinput;
   char buf[12]; // needs to be at least large enough to fit the formatted text
   if (gps.location.isValid())
  {
    gpsinput = gps.location.lat();
    Serial.print(gps.location.lat());
    sprintf(buf," ",gpsinput);
    latitude = buf;
    
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    
    gpsinput = gps.location.lng();
    sprintf(buf," ",gpsinput);
    longitude = buf;
  }
  else
  {
    Serial.print(F("INVALID"));
    sprintf(buf,"INVALID",gpsinput);
  }
  
    Serial.print(F("  Date: "));
  if (gps.date.isValid())
  {
    gpsinput = gps.date.day();
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
  
  if (gps.time.isValid())
  {
    Serial.print(F("  Time: "));
    if (gps.time.hour() < 10) radioSerial.print(F("0"));
    Serial.print(gps.time.hour()+2);
    Serial.print(F(":"));
    if (gps.time.minute() < 10) radioSerial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) radioSerial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) radioSerial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
}

