#include <SoftwareSerial.h>
#include "C:\Users\Matt\Documents\Arduino\libraries\mavlink\include\solarCarFINAL\solarCar\mavlink.h" 

#define BAUDRATE 9600
static const int RXPin = 4, TXPin = 3;
SoftwareSerial radioSerial(RXPin, TXPin); //to send serial RF

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radioSerial.begin(BAUDRATE);
  Serial.println(F("Setup starting"));
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println("sending packet values: "); 
    
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
	
	// Pack the message
	// mavlink_message_heartbeat_pack(system id, component id, message container, system type, MAV_AUTOPILOT_GENERIC)
	mavlink_msg_heartbeat_pack(100, 200, &msg, system_type, autopilot_type,base_mode,custom_mode,system_status);
	
        //convenience function is msg_sys_status_pack for sending all status msgs
        //mavlink_msg_sys_status_pack( system_id, component_id, mavlink_message_t* msg, base_mode, nav_mode,status,vbat,motor_block, packet_drop)
        //randomly switches out system status values for show on QGC

	// Copy the message to send buffer 
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	
        delay(1000);
	// Send the message (.write sends as bytes) 
        Serial.println("Sending MAVLink Packet");
	Serial.write(buf, len);
}
 

