/** @file
 *	@brief MAVLink comm protocol testsuite generated from solarCar.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef SOLARCAR_TESTSUITE_H
#define SOLARCAR_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_solarCar(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

	mavlink_test_solarCar(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_heartbeat(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_heartbeat_t packet_in = {
		963497464,17,84,151,218,2
    };
	mavlink_heartbeat_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.custom_mode = packet_in.custom_mode;
        	packet1.type = packet_in.type;
        	packet1.autopilot = packet_in.autopilot;
        	packet1.base_mode = packet_in.base_mode;
        	packet1.system_status = packet_in.system_status;
        	packet1.mavlink_version = packet_in.mavlink_version;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_heartbeat_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_heartbeat_pack(system_id, component_id, &msg , packet1.type , packet1.autopilot , packet1.base_mode , packet1.custom_mode , packet1.system_status );
	mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_heartbeat_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.type , packet1.autopilot , packet1.base_mode , packet1.custom_mode , packet1.system_status );
	mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_heartbeat_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_heartbeat_send(MAVLINK_COMM_1 , packet1.type , packet1.autopilot , packet1.base_mode , packet1.custom_mode , packet1.system_status );
	mavlink_msg_heartbeat_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_bms_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_bms_data_t packet_in = {
		963497464,963497672,17651,17755,17859,17963,18067,18171,18275,199,10,77,144,211,22,89,156,223,34,101,168,235,46,113,180,247,2
    };
	mavlink_bms_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.batteryEnergyIn = packet_in.batteryEnergyIn;
        	packet1.batteryEnergyOut = packet_in.batteryEnergyOut;
        	packet1.packVoltage = packet_in.packVoltage;
        	packet1.current = packet_in.current;
        	packet1.currentLimit = packet_in.currentLimit;
        	packet1.dischargeLimit = packet_in.dischargeLimit;
        	packet1.DOD = packet_in.DOD;
        	packet1.capacity = packet_in.capacity;
        	packet1.packResistance = packet_in.packResistance;
        	packet1.fault_flags = packet_in.fault_flags;
        	packet1.maxVoltage = packet_in.maxVoltage;
        	packet1.maxVoltageID = packet_in.maxVoltageID;
        	packet1.minVoltage = packet_in.minVoltage;
        	packet1.minVoltageID = packet_in.minVoltageID;
        	packet1.SOC = packet_in.SOC;
        	packet1.SOH = packet_in.SOH;
        	packet1.minTempID = packet_in.minTempID;
        	packet1.minTemp = packet_in.minTemp;
        	packet1.temperature = packet_in.temperature;
        	packet1.maxTemp = packet_in.maxTemp;
        	packet1.maxTempID = packet_in.maxTempID;
        	packet1.minRes = packet_in.minRes;
        	packet1.minResID = packet_in.minResID;
        	packet1.maxRes = packet_in.maxRes;
        	packet1.maxResID = packet_in.maxResID;
        	packet1.system_status = packet_in.system_status;
        	packet1.mavlink_version = packet_in.mavlink_version;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bms_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_bms_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bms_data_pack(system_id, component_id, &msg , packet1.fault_flags , packet1.maxVoltage , packet1.maxVoltageID , packet1.minVoltage , packet1.minVoltageID , packet1.packVoltage , packet1.current , packet1.currentLimit , packet1.dischargeLimit , packet1.batteryEnergyIn , packet1.batteryEnergyOut , packet1.SOC , packet1.DOD , packet1.capacity , packet1.SOH , packet1.minTempID , packet1.minTemp , packet1.temperature , packet1.maxTemp , packet1.maxTempID , packet1.packResistance , packet1.minRes , packet1.minResID , packet1.maxRes , packet1.maxResID , packet1.system_status );
	mavlink_msg_bms_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bms_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.fault_flags , packet1.maxVoltage , packet1.maxVoltageID , packet1.minVoltage , packet1.minVoltageID , packet1.packVoltage , packet1.current , packet1.currentLimit , packet1.dischargeLimit , packet1.batteryEnergyIn , packet1.batteryEnergyOut , packet1.SOC , packet1.DOD , packet1.capacity , packet1.SOH , packet1.minTempID , packet1.minTemp , packet1.temperature , packet1.maxTemp , packet1.maxTempID , packet1.packResistance , packet1.minRes , packet1.minResID , packet1.maxRes , packet1.maxResID , packet1.system_status );
	mavlink_msg_bms_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_bms_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bms_data_send(MAVLINK_COMM_1 , packet1.fault_flags , packet1.maxVoltage , packet1.maxVoltageID , packet1.minVoltage , packet1.minVoltageID , packet1.packVoltage , packet1.current , packet1.currentLimit , packet1.dischargeLimit , packet1.batteryEnergyIn , packet1.batteryEnergyOut , packet1.SOC , packet1.DOD , packet1.capacity , packet1.SOH , packet1.minTempID , packet1.minTemp , packet1.temperature , packet1.maxTemp , packet1.maxTempID , packet1.packResistance , packet1.minRes , packet1.minResID , packet1.maxRes , packet1.maxResID , packet1.system_status );
	mavlink_msg_bms_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mppt1_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_mppt1_data_t packet_in = {
		17235,17339,17443,151,218
    };
	mavlink_mppt1_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.voltage_in = packet_in.voltage_in;
        	packet1.current_in = packet_in.current_in;
        	packet1.voltage_out = packet_in.voltage_out;
        	packet1.ambient_temp = packet_in.ambient_temp;
        	packet1.status = packet_in.status;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt1_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_mppt1_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt1_data_pack(system_id, component_id, &msg , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt1_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt1_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt1_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_mppt1_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt1_data_send(MAVLINK_COMM_1 , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt1_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mppt2_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_mppt2_data_t packet_in = {
		17235,17339,17443,151,218
    };
	mavlink_mppt2_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.voltage_in = packet_in.voltage_in;
        	packet1.current_in = packet_in.current_in;
        	packet1.voltage_out = packet_in.voltage_out;
        	packet1.ambient_temp = packet_in.ambient_temp;
        	packet1.status = packet_in.status;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt2_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_mppt2_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt2_data_pack(system_id, component_id, &msg , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt2_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt2_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt2_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_mppt2_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt2_data_send(MAVLINK_COMM_1 , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt2_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mppt3_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_mppt3_data_t packet_in = {
		17235,17339,17443,151,218
    };
	mavlink_mppt3_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.voltage_in = packet_in.voltage_in;
        	packet1.current_in = packet_in.current_in;
        	packet1.voltage_out = packet_in.voltage_out;
        	packet1.ambient_temp = packet_in.ambient_temp;
        	packet1.status = packet_in.status;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt3_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_mppt3_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt3_data_pack(system_id, component_id, &msg , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt3_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt3_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt3_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_mppt3_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt3_data_send(MAVLINK_COMM_1 , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt3_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mppt4_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_mppt4_data_t packet_in = {
		17235,17339,17443,151,218
    };
	mavlink_mppt4_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.voltage_in = packet_in.voltage_in;
        	packet1.current_in = packet_in.current_in;
        	packet1.voltage_out = packet_in.voltage_out;
        	packet1.ambient_temp = packet_in.ambient_temp;
        	packet1.status = packet_in.status;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt4_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_mppt4_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt4_data_pack(system_id, component_id, &msg , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt4_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt4_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt4_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_mppt4_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt4_data_send(MAVLINK_COMM_1 , packet1.voltage_in , packet1.current_in , packet1.voltage_out , packet1.ambient_temp , packet1.status );
	mavlink_msg_mppt4_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_speed_halleffect(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_speed_halleffect_t packet_in = {
		17235,17339,17,84,151,218
    };
	mavlink_speed_halleffect_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.hes_RPM = packet_in.hes_RPM;
        	packet1.motor_RPM = packet_in.motor_RPM;
        	packet1.avg_speed = packet_in.avg_speed;
        	packet1.hes_speed = packet_in.hes_speed;
        	packet1.motor_speed = packet_in.motor_speed;
        	packet1.flags = packet_in.flags;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_speed_halleffect_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_speed_halleffect_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_speed_halleffect_pack(system_id, component_id, &msg , packet1.avg_speed , packet1.hes_speed , packet1.hes_RPM , packet1.motor_speed , packet1.motor_RPM , packet1.flags );
	mavlink_msg_speed_halleffect_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_speed_halleffect_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.avg_speed , packet1.hes_speed , packet1.hes_RPM , packet1.motor_speed , packet1.motor_RPM , packet1.flags );
	mavlink_msg_speed_halleffect_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_speed_halleffect_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_speed_halleffect_send(MAVLINK_COMM_1 , packet1.avg_speed , packet1.hes_speed , packet1.hes_RPM , packet1.motor_speed , packet1.motor_RPM , packet1.flags );
	mavlink_msg_speed_halleffect_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_gps(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_gps_t packet_in = {
		"ABCDEFGHIJK","MNOPQRSTUVW","YZABCDEFGHI","KLMNOPQRSTU","WXYZABCDEFG"
    };
	mavlink_gps_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        	mav_array_memcpy(packet1.latitude, packet_in.latitude, sizeof(char)*12);
        	mav_array_memcpy(packet1.longitude, packet_in.longitude, sizeof(char)*12);
        	mav_array_memcpy(packet1.time, packet_in.time, sizeof(char)*12);
        	mav_array_memcpy(packet1.date, packet_in.date, sizeof(char)*12);
        	mav_array_memcpy(packet1.lock_error, packet_in.lock_error, sizeof(char)*12);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_gps_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_gps_pack(system_id, component_id, &msg , packet1.latitude , packet1.longitude , packet1.time , packet1.date , packet1.lock_error );
	mavlink_msg_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_gps_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.latitude , packet1.longitude , packet1.time , packet1.date , packet1.lock_error );
	mavlink_msg_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_gps_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_gps_send(MAVLINK_COMM_1 , packet1.latitude , packet1.longitude , packet1.time , packet1.date , packet1.lock_error );
	mavlink_msg_gps_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_accelo_gyro(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_accelo_gyro_t packet_in = {
		5,72
    };
	mavlink_accelo_gyro_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.acceleration = packet_in.acceleration;
        	packet1.incline = packet_in.incline;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_accelo_gyro_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_accelo_gyro_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_accelo_gyro_pack(system_id, component_id, &msg , packet1.acceleration , packet1.incline );
	mavlink_msg_accelo_gyro_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_accelo_gyro_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.acceleration , packet1.incline );
	mavlink_msg_accelo_gyro_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_accelo_gyro_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_accelo_gyro_send(MAVLINK_COMM_1 , packet1.acceleration , packet1.incline );
	mavlink_msg_accelo_gyro_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_extra1(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_extra1_t packet_in = {
		17235,139,206
    };
	mavlink_extra1_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.extra3 = packet_in.extra3;
        	packet1.extra1 = packet_in.extra1;
        	packet1.extra2 = packet_in.extra2;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra1_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_extra1_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra1_pack(system_id, component_id, &msg , packet1.extra1 , packet1.extra2 , packet1.extra3 );
	mavlink_msg_extra1_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra1_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.extra1 , packet1.extra2 , packet1.extra3 );
	mavlink_msg_extra1_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_extra1_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra1_send(MAVLINK_COMM_1 , packet1.extra1 , packet1.extra2 , packet1.extra3 );
	mavlink_msg_extra1_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_extra2(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_extra2_t packet_in = {
		17235,139,206
    };
	mavlink_extra2_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.extra3 = packet_in.extra3;
        	packet1.extra1 = packet_in.extra1;
        	packet1.extra2 = packet_in.extra2;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra2_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_extra2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra2_pack(system_id, component_id, &msg , packet1.extra1 , packet1.extra2 , packet1.extra3 );
	mavlink_msg_extra2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra2_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.extra1 , packet1.extra2 , packet1.extra3 );
	mavlink_msg_extra2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_extra2_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra2_send(MAVLINK_COMM_1 , packet1.extra1 , packet1.extra2 , packet1.extra3 );
	mavlink_msg_extra2_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_extra3(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_extra3_t packet_in = {
		17235,139,206
    };
	mavlink_extra3_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.extra3 = packet_in.extra3;
        	packet1.extra1 = packet_in.extra1;
        	packet1.extra2 = packet_in.extra2;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra3_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_extra3_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra3_pack(system_id, component_id, &msg , packet1.extra1 , packet1.extra2 , packet1.extra3 );
	mavlink_msg_extra3_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra3_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.extra1 , packet1.extra2 , packet1.extra3 );
	mavlink_msg_extra3_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_extra3_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_extra3_send(MAVLINK_COMM_1 , packet1.extra1 , packet1.extra2 , packet1.extra3 );
	mavlink_msg_extra3_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_solarCar(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_heartbeat(system_id, component_id, last_msg);
	mavlink_test_bms_data(system_id, component_id, last_msg);
	mavlink_test_mppt1_data(system_id, component_id, last_msg);
	mavlink_test_mppt2_data(system_id, component_id, last_msg);
	mavlink_test_mppt3_data(system_id, component_id, last_msg);
	mavlink_test_mppt4_data(system_id, component_id, last_msg);
	mavlink_test_speed_halleffect(system_id, component_id, last_msg);
	mavlink_test_gps(system_id, component_id, last_msg);
	mavlink_test_accelo_gyro(system_id, component_id, last_msg);
	mavlink_test_extra1(system_id, component_id, last_msg);
	mavlink_test_extra2(system_id, component_id, last_msg);
	mavlink_test_extra3(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // SOLARCAR_TESTSUITE_H
