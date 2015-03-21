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
		2.2,1.2,125,{ 5.1, 5.6, 5.9 },{ 32, 45, 51 },0,'t',0,0,86,192,2
    };
	mavlink_bms_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.source_current = packet_in.source_current;
        	packet1.load_current = packet_in.load_current;
        	packet1.pack_voltage = packet_in.pack_voltage;
        	packet1.fault_condition = packet_in.fault_condition;
        	packet1.bat_fan_status = packet_in.bat_fan_status;
        	packet1.LLIM_state = packet_in.LLIM_state;
        	packet1.HLIM_state = packet_in.HLIM_state;
        	packet1.state_of_chg = packet_in.state_of_chg;
        	packet1.system_status = packet_in.system_status;
        	packet1.mavlink_version = packet_in.mavlink_version;
        
        	mav_array_memcpy(packet1.cell_voltages, packet_in.cell_voltages, sizeof(float)*3);
        	mav_array_memcpy(packet1.cell_temps, packet_in.cell_temps, sizeof(float)*3);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bms_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_bms_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bms_data_pack(system_id, component_id, &msg , packet1.fault_condition , packet1.source_current , packet1.load_current , packet1.bat_fan_status , packet1.LLIM_state , packet1.HLIM_state , packet1.state_of_chg , packet1.pack_voltage , packet1.cell_voltages , packet1.cell_temps , packet1.system_status );
	mavlink_msg_bms_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_bms_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.fault_condition , packet1.source_current , packet1.load_current , packet1.bat_fan_status , packet1.LLIM_state , packet1.HLIM_state , packet1.state_of_chg , packet1.pack_voltage , packet1.cell_voltages , packet1.cell_temps , packet1.system_status );
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
	mavlink_msg_bms_data_send(MAVLINK_COMM_1 , packet1.fault_condition , packet1.source_current , packet1.load_current , packet1.bat_fan_status , packet1.LLIM_state , packet1.HLIM_state , packet1.state_of_chg , packet1.pack_voltage , packet1.cell_voltages , packet1.cell_temps , packet1.system_status );
	mavlink_msg_bms_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mppt1_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_mppt1_data_t packet_in = {
		55,2.1,0,0
    };
	mavlink_mppt1_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.voltage_in = packet_in.voltage_in;
        	packet1.current_in = packet_in.current_in;
        	packet1.overtemp = packet_in.overtemp;
        	packet1.undervolt = packet_in.undervolt;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt1_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_mppt1_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt1_data_pack(system_id, component_id, &msg , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
	mavlink_msg_mppt1_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt1_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
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
	mavlink_msg_mppt1_data_send(MAVLINK_COMM_1 , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
	mavlink_msg_mppt1_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mppt2_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_mppt2_data_t packet_in = {
		52,2.3,0,0
    };
	mavlink_mppt2_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.voltage_in = packet_in.voltage_in;
        	packet1.current_in = packet_in.current_in;
        	packet1.overtemp = packet_in.overtemp;
        	packet1.undervolt = packet_in.undervolt;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt2_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_mppt2_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt2_data_pack(system_id, component_id, &msg , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
	mavlink_msg_mppt2_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt2_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
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
	mavlink_msg_mppt2_data_send(MAVLINK_COMM_1 , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
	mavlink_msg_mppt2_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mppt3_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_mppt3_data_t packet_in = {
		51,2.5,0,0
    };
	mavlink_mppt3_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.voltage_in = packet_in.voltage_in;
        	packet1.current_in = packet_in.current_in;
        	packet1.overtemp = packet_in.overtemp;
        	packet1.undervolt = packet_in.undervolt;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt3_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_mppt3_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt3_data_pack(system_id, component_id, &msg , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
	mavlink_msg_mppt3_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt3_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
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
	mavlink_msg_mppt3_data_send(MAVLINK_COMM_1 , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
	mavlink_msg_mppt3_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_mppt4_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_mppt4_data_t packet_in = {
		59,2.8,0,0
    };
	mavlink_mppt4_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.voltage_in = packet_in.voltage_in;
        	packet1.current_in = packet_in.current_in;
        	packet1.overtemp = packet_in.overtemp;
        	packet1.undervolt = packet_in.undervolt;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt4_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_mppt4_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt4_data_pack(system_id, component_id, &msg , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
	mavlink_msg_mppt4_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_mppt4_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
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
	mavlink_msg_mppt4_data_send(MAVLINK_COMM_1 , packet1.voltage_in , packet1.current_in , packet1.overtemp , packet1.undervolt );
	mavlink_msg_mppt4_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_motor_driver(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_motor_driver_t packet_in = {
		5,72
    };
	mavlink_motor_driver_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.controller_temp = packet_in.controller_temp;
        	packet1.speed = packet_in.speed;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_motor_driver_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_motor_driver_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_motor_driver_pack(system_id, component_id, &msg , packet1.controller_temp , packet1.speed );
	mavlink_msg_motor_driver_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_motor_driver_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.controller_temp , packet1.speed );
	mavlink_msg_motor_driver_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_motor_driver_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_motor_driver_send(MAVLINK_COMM_1 , packet1.controller_temp , packet1.speed );
	mavlink_msg_motor_driver_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_gps(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_gps_t packet_in = {
		"-26 30'32''","30 27'11''","11/03/2015","13:23","LOCKED"
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

static void mavlink_test_solarCar(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_heartbeat(system_id, component_id, last_msg);
	mavlink_test_bms_data(system_id, component_id, last_msg);
	mavlink_test_mppt1_data(system_id, component_id, last_msg);
	mavlink_test_mppt2_data(system_id, component_id, last_msg);
	mavlink_test_mppt3_data(system_id, component_id, last_msg);
	mavlink_test_mppt4_data(system_id, component_id, last_msg);
	mavlink_test_motor_driver(system_id, component_id, last_msg);
	mavlink_test_gps(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // SOLARCAR_TESTSUITE_H
