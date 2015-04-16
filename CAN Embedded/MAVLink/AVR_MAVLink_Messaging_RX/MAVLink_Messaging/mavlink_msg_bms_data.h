// MESSAGE BMS_DATA PACKING

#define MAVLINK_MSG_ID_BMS_DATA 150

typedef struct __mavlink_bms_data_t
{
 uint16_t source_current; ///< Battery source current (0-65535mA) 
 uint16_t load_current; ///< Battery load current (0-65535mA)
 uint16_t pack_voltage; ///< Value to indicate the voltage of the pack (0-65536V)
 uint16_t cell_voltages[3]; ///< cell voltage parameters [minimum, average, maximum]
 uint16_t cell_temps[3]; ///< cell temperature parameters [minimum, average, maximum]
 uint8_t fault_condition; ///< Value to indicate a fault condition ('1' = fault condition, '0' = no fault)
 char bat_fan_status; ///< Char to indicate battery fan status, 't' = okay; 'f' = fault condition
 uint8_t LLIM_state; ///< logic low limit flag for stopping discharging. '1'=flag active; '0'=flag not active 
 uint8_t HLIM_state; ///< logic high limit flag for stopping charging. '1'=flag active; '0'=flag not active 
 uint8_t state_of_chg; ///< Percentage battery charge, 0-100
 uint8_t system_status; ///< System status flag, see MAV_STATE ENUM
 uint8_t mavlink_version; ///< MAVLink version
} mavlink_bms_data_t;

#define MAVLINK_MSG_ID_BMS_DATA_LEN 25
#define MAVLINK_MSG_ID_150_LEN 25

#define MAVLINK_MSG_ID_BMS_DATA_CRC 92
#define MAVLINK_MSG_ID_150_CRC 92

#define MAVLINK_MSG_BMS_DATA_FIELD_CELL_VOLTAGES_LEN 3
#define MAVLINK_MSG_BMS_DATA_FIELD_CELL_TEMPS_LEN 3

#define MAVLINK_MESSAGE_INFO_BMS_DATA { \
	"BMS_DATA", \
	12, \
	{  { "source_current", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_bms_data_t, source_current) }, \
         { "load_current", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_bms_data_t, load_current) }, \
         { "pack_voltage", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_bms_data_t, pack_voltage) }, \
         { "cell_voltages", NULL, MAVLINK_TYPE_UINT16_T, 3, 6, offsetof(mavlink_bms_data_t, cell_voltages) }, \
         { "cell_temps", NULL, MAVLINK_TYPE_UINT16_T, 3, 12, offsetof(mavlink_bms_data_t, cell_temps) }, \
         { "fault_condition", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_bms_data_t, fault_condition) }, \
         { "bat_fan_status", NULL, MAVLINK_TYPE_CHAR, 0, 19, offsetof(mavlink_bms_data_t, bat_fan_status) }, \
         { "LLIM_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_bms_data_t, LLIM_state) }, \
         { "HLIM_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_bms_data_t, HLIM_state) }, \
         { "state_of_chg", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_bms_data_t, state_of_chg) }, \
         { "system_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 23, offsetof(mavlink_bms_data_t, system_status) }, \
         { "mavlink_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_bms_data_t, mavlink_version) }, \
         } \
}


/**
 * @brief Pack a bms_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param fault_condition Value to indicate a fault condition ('1' = fault condition, '0' = no fault)
 * @param source_current Battery source current (0-65535mA) 
 * @param load_current Battery load current (0-65535mA)
 * @param bat_fan_status Char to indicate battery fan status, 't' = okay; 'f' = fault condition
 * @param LLIM_state logic low limit flag for stopping discharging. '1'=flag active; '0'=flag not active 
 * @param HLIM_state logic high limit flag for stopping charging. '1'=flag active; '0'=flag not active 
 * @param state_of_chg Percentage battery charge, 0-100
 * @param pack_voltage Value to indicate the voltage of the pack (0-65536V)
 * @param cell_voltages cell voltage parameters [minimum, average, maximum]
 * @param cell_temps cell temperature parameters [minimum, average, maximum]
 * @param system_status System status flag, see MAV_STATE ENUM
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_bms_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t fault_condition, uint16_t source_current, uint16_t load_current, char bat_fan_status, uint8_t LLIM_state, uint8_t HLIM_state, uint8_t state_of_chg, uint16_t pack_voltage, const uint16_t *cell_voltages, const uint16_t *cell_temps, uint8_t system_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BMS_DATA_LEN];
	_mav_put_uint16_t(buf, 0, source_current);
	_mav_put_uint16_t(buf, 2, load_current);
	_mav_put_uint16_t(buf, 4, pack_voltage);
	_mav_put_uint8_t(buf, 18, fault_condition);
	_mav_put_char(buf, 19, bat_fan_status);
	_mav_put_uint8_t(buf, 20, LLIM_state);
	_mav_put_uint8_t(buf, 21, HLIM_state);
	_mav_put_uint8_t(buf, 22, state_of_chg);
	_mav_put_uint8_t(buf, 23, system_status);
	_mav_put_uint8_t(buf, 24, 2);
	_mav_put_uint16_t_array(buf, 6, cell_voltages, 3);
	_mav_put_uint16_t_array(buf, 12, cell_temps, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BMS_DATA_LEN);
#else
	mavlink_bms_data_t packet;
	packet.source_current = source_current;
	packet.load_current = load_current;
	packet.pack_voltage = pack_voltage;
	packet.fault_condition = fault_condition;
	packet.bat_fan_status = bat_fan_status;
	packet.LLIM_state = LLIM_state;
	packet.HLIM_state = HLIM_state;
	packet.state_of_chg = state_of_chg;
	packet.system_status = system_status;
	packet.mavlink_version = 2;
	mav_array_memcpy(packet.cell_voltages, cell_voltages, sizeof(uint16_t)*3);
	mav_array_memcpy(packet.cell_temps, cell_temps, sizeof(uint16_t)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BMS_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BMS_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BMS_DATA_LEN, MAVLINK_MSG_ID_BMS_DATA_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BMS_DATA_LEN);
#endif
}

/**
 * @brief Pack a bms_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fault_condition Value to indicate a fault condition ('1' = fault condition, '0' = no fault)
 * @param source_current Battery source current (0-65535mA) 
 * @param load_current Battery load current (0-65535mA)
 * @param bat_fan_status Char to indicate battery fan status, 't' = okay; 'f' = fault condition
 * @param LLIM_state logic low limit flag for stopping discharging. '1'=flag active; '0'=flag not active 
 * @param HLIM_state logic high limit flag for stopping charging. '1'=flag active; '0'=flag not active 
 * @param state_of_chg Percentage battery charge, 0-100
 * @param pack_voltage Value to indicate the voltage of the pack (0-65536V)
 * @param cell_voltages cell voltage parameters [minimum, average, maximum]
 * @param cell_temps cell temperature parameters [minimum, average, maximum]
 * @param system_status System status flag, see MAV_STATE ENUM
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_bms_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t fault_condition,uint16_t source_current,uint16_t load_current,char bat_fan_status,uint8_t LLIM_state,uint8_t HLIM_state,uint8_t state_of_chg,uint16_t pack_voltage,const uint16_t *cell_voltages,const uint16_t *cell_temps,uint8_t system_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BMS_DATA_LEN];
	_mav_put_uint16_t(buf, 0, source_current);
	_mav_put_uint16_t(buf, 2, load_current);
	_mav_put_uint16_t(buf, 4, pack_voltage);
	_mav_put_uint8_t(buf, 18, fault_condition);
	_mav_put_char(buf, 19, bat_fan_status);
	_mav_put_uint8_t(buf, 20, LLIM_state);
	_mav_put_uint8_t(buf, 21, HLIM_state);
	_mav_put_uint8_t(buf, 22, state_of_chg);
	_mav_put_uint8_t(buf, 23, system_status);
	_mav_put_uint8_t(buf, 24, 2);
	_mav_put_uint16_t_array(buf, 6, cell_voltages, 3);
	_mav_put_uint16_t_array(buf, 12, cell_temps, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BMS_DATA_LEN);
#else
	mavlink_bms_data_t packet;
	packet.source_current = source_current;
	packet.load_current = load_current;
	packet.pack_voltage = pack_voltage;
	packet.fault_condition = fault_condition;
	packet.bat_fan_status = bat_fan_status;
	packet.LLIM_state = LLIM_state;
	packet.HLIM_state = HLIM_state;
	packet.state_of_chg = state_of_chg;
	packet.system_status = system_status;
	packet.mavlink_version = 2;
	mav_array_memcpy(packet.cell_voltages, cell_voltages, sizeof(uint16_t)*3);
	mav_array_memcpy(packet.cell_temps, cell_temps, sizeof(uint16_t)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BMS_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_BMS_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BMS_DATA_LEN, MAVLINK_MSG_ID_BMS_DATA_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BMS_DATA_LEN);
#endif
}

/**
 * @brief Encode a bms_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param bms_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_bms_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_bms_data_t* bms_data)
{
	return mavlink_msg_bms_data_pack(system_id, component_id, msg, bms_data->fault_condition, bms_data->source_current, bms_data->load_current, bms_data->bat_fan_status, bms_data->LLIM_state, bms_data->HLIM_state, bms_data->state_of_chg, bms_data->pack_voltage, bms_data->cell_voltages, bms_data->cell_temps, bms_data->system_status);
}

/**
 * @brief Encode a bms_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param bms_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_bms_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_bms_data_t* bms_data)
{
	return mavlink_msg_bms_data_pack_chan(system_id, component_id, chan, msg, bms_data->fault_condition, bms_data->source_current, bms_data->load_current, bms_data->bat_fan_status, bms_data->LLIM_state, bms_data->HLIM_state, bms_data->state_of_chg, bms_data->pack_voltage, bms_data->cell_voltages, bms_data->cell_temps, bms_data->system_status);
}

/**
 * @brief Send a bms_data message
 * @param chan MAVLink channel to send the message
 *
 * @param fault_condition Value to indicate a fault condition ('1' = fault condition, '0' = no fault)
 * @param source_current Battery source current (0-65535mA) 
 * @param load_current Battery load current (0-65535mA)
 * @param bat_fan_status Char to indicate battery fan status, 't' = okay; 'f' = fault condition
 * @param LLIM_state logic low limit flag for stopping discharging. '1'=flag active; '0'=flag not active 
 * @param HLIM_state logic high limit flag for stopping charging. '1'=flag active; '0'=flag not active 
 * @param state_of_chg Percentage battery charge, 0-100
 * @param pack_voltage Value to indicate the voltage of the pack (0-65536V)
 * @param cell_voltages cell voltage parameters [minimum, average, maximum]
 * @param cell_temps cell temperature parameters [minimum, average, maximum]
 * @param system_status System status flag, see MAV_STATE ENUM
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_bms_data_send(mavlink_channel_t chan, uint8_t fault_condition, uint16_t source_current, uint16_t load_current, char bat_fan_status, uint8_t LLIM_state, uint8_t HLIM_state, uint8_t state_of_chg, uint16_t pack_voltage, const uint16_t *cell_voltages, const uint16_t *cell_temps, uint8_t system_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_BMS_DATA_LEN];
	_mav_put_uint16_t(buf, 0, source_current);
	_mav_put_uint16_t(buf, 2, load_current);
	_mav_put_uint16_t(buf, 4, pack_voltage);
	_mav_put_uint8_t(buf, 18, fault_condition);
	_mav_put_char(buf, 19, bat_fan_status);
	_mav_put_uint8_t(buf, 20, LLIM_state);
	_mav_put_uint8_t(buf, 21, HLIM_state);
	_mav_put_uint8_t(buf, 22, state_of_chg);
	_mav_put_uint8_t(buf, 23, system_status);
	_mav_put_uint8_t(buf, 24, 2);
	_mav_put_uint16_t_array(buf, 6, cell_voltages, 3);
	_mav_put_uint16_t_array(buf, 12, cell_temps, 3);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BMS_DATA, buf, MAVLINK_MSG_ID_BMS_DATA_LEN, MAVLINK_MSG_ID_BMS_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BMS_DATA, buf, MAVLINK_MSG_ID_BMS_DATA_LEN);
#endif
#else
	mavlink_bms_data_t packet;
	packet.source_current = source_current;
	packet.load_current = load_current;
	packet.pack_voltage = pack_voltage;
	packet.fault_condition = fault_condition;
	packet.bat_fan_status = bat_fan_status;
	packet.LLIM_state = LLIM_state;
	packet.HLIM_state = HLIM_state;
	packet.state_of_chg = state_of_chg;
	packet.system_status = system_status;
	packet.mavlink_version = 2;
	mav_array_memcpy(packet.cell_voltages, cell_voltages, sizeof(uint16_t)*3);
	mav_array_memcpy(packet.cell_temps, cell_temps, sizeof(uint16_t)*3);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BMS_DATA, (const char *)&packet, MAVLINK_MSG_ID_BMS_DATA_LEN, MAVLINK_MSG_ID_BMS_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BMS_DATA, (const char *)&packet, MAVLINK_MSG_ID_BMS_DATA_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_BMS_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_bms_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t fault_condition, uint16_t source_current, uint16_t load_current, char bat_fan_status, uint8_t LLIM_state, uint8_t HLIM_state, uint8_t state_of_chg, uint16_t pack_voltage, const uint16_t *cell_voltages, const uint16_t *cell_temps, uint8_t system_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint16_t(buf, 0, source_current);
	_mav_put_uint16_t(buf, 2, load_current);
	_mav_put_uint16_t(buf, 4, pack_voltage);
	_mav_put_uint8_t(buf, 18, fault_condition);
	_mav_put_char(buf, 19, bat_fan_status);
	_mav_put_uint8_t(buf, 20, LLIM_state);
	_mav_put_uint8_t(buf, 21, HLIM_state);
	_mav_put_uint8_t(buf, 22, state_of_chg);
	_mav_put_uint8_t(buf, 23, system_status);
	_mav_put_uint8_t(buf, 24, 2);
	_mav_put_uint16_t_array(buf, 6, cell_voltages, 3);
	_mav_put_uint16_t_array(buf, 12, cell_temps, 3);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BMS_DATA, buf, MAVLINK_MSG_ID_BMS_DATA_LEN, MAVLINK_MSG_ID_BMS_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BMS_DATA, buf, MAVLINK_MSG_ID_BMS_DATA_LEN);
#endif
#else
	mavlink_bms_data_t *packet = (mavlink_bms_data_t *)msgbuf;
	packet->source_current = source_current;
	packet->load_current = load_current;
	packet->pack_voltage = pack_voltage;
	packet->fault_condition = fault_condition;
	packet->bat_fan_status = bat_fan_status;
	packet->LLIM_state = LLIM_state;
	packet->HLIM_state = HLIM_state;
	packet->state_of_chg = state_of_chg;
	packet->system_status = system_status;
	packet->mavlink_version = 2;
	mav_array_memcpy(packet->cell_voltages, cell_voltages, sizeof(uint16_t)*3);
	mav_array_memcpy(packet->cell_temps, cell_temps, sizeof(uint16_t)*3);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BMS_DATA, (const char *)packet, MAVLINK_MSG_ID_BMS_DATA_LEN, MAVLINK_MSG_ID_BMS_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BMS_DATA, (const char *)packet, MAVLINK_MSG_ID_BMS_DATA_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE BMS_DATA UNPACKING


/**
 * @brief Get field fault_condition from bms_data message
 *
 * @return Value to indicate a fault condition ('1' = fault condition, '0' = no fault)
 */
static inline uint8_t mavlink_msg_bms_data_get_fault_condition(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  18);
}

/**
 * @brief Get field source_current from bms_data message
 *
 * @return Battery source current (0-65535mA) 
 */
static inline uint16_t mavlink_msg_bms_data_get_source_current(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field load_current from bms_data message
 *
 * @return Battery load current (0-65535mA)
 */
static inline uint16_t mavlink_msg_bms_data_get_load_current(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field bat_fan_status from bms_data message
 *
 * @return Char to indicate battery fan status, 't' = okay; 'f' = fault condition
 */
static inline char mavlink_msg_bms_data_get_bat_fan_status(const mavlink_message_t* msg)
{
	return _MAV_RETURN_char(msg,  19);
}

/**
 * @brief Get field LLIM_state from bms_data message
 *
 * @return logic low limit flag for stopping discharging. '1'=flag active; '0'=flag not active 
 */
static inline uint8_t mavlink_msg_bms_data_get_LLIM_state(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  20);
}

/**
 * @brief Get field HLIM_state from bms_data message
 *
 * @return logic high limit flag for stopping charging. '1'=flag active; '0'=flag not active 
 */
static inline uint8_t mavlink_msg_bms_data_get_HLIM_state(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  21);
}

/**
 * @brief Get field state_of_chg from bms_data message
 *
 * @return Percentage battery charge, 0-100
 */
static inline uint8_t mavlink_msg_bms_data_get_state_of_chg(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  22);
}

/**
 * @brief Get field pack_voltage from bms_data message
 *
 * @return Value to indicate the voltage of the pack (0-65536V)
 */
static inline uint16_t mavlink_msg_bms_data_get_pack_voltage(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field cell_voltages from bms_data message
 *
 * @return cell voltage parameters [minimum, average, maximum]
 */
static inline uint16_t mavlink_msg_bms_data_get_cell_voltages(const mavlink_message_t* msg, uint16_t *cell_voltages)
{
	return _MAV_RETURN_uint16_t_array(msg, cell_voltages, 3,  6);
}

/**
 * @brief Get field cell_temps from bms_data message
 *
 * @return cell temperature parameters [minimum, average, maximum]
 */
static inline uint16_t mavlink_msg_bms_data_get_cell_temps(const mavlink_message_t* msg, uint16_t *cell_temps)
{
	return _MAV_RETURN_uint16_t_array(msg, cell_temps, 3,  12);
}

/**
 * @brief Get field system_status from bms_data message
 *
 * @return System status flag, see MAV_STATE ENUM
 */
static inline uint8_t mavlink_msg_bms_data_get_system_status(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  23);
}

/**
 * @brief Get field mavlink_version from bms_data message
 *
 * @return MAVLink version
 */
static inline uint8_t mavlink_msg_bms_data_get_mavlink_version(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Decode a bms_data message into a struct
 *
 * @param msg The message to decode
 * @param bms_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_bms_data_decode(const mavlink_message_t* msg, mavlink_bms_data_t* bms_data)
{
#if MAVLINK_NEED_BYTE_SWAP
	bms_data->source_current = mavlink_msg_bms_data_get_source_current(msg);
	bms_data->load_current = mavlink_msg_bms_data_get_load_current(msg);
	bms_data->pack_voltage = mavlink_msg_bms_data_get_pack_voltage(msg);
	mavlink_msg_bms_data_get_cell_voltages(msg, bms_data->cell_voltages);
	mavlink_msg_bms_data_get_cell_temps(msg, bms_data->cell_temps);
	bms_data->fault_condition = mavlink_msg_bms_data_get_fault_condition(msg);
	bms_data->bat_fan_status = mavlink_msg_bms_data_get_bat_fan_status(msg);
	bms_data->LLIM_state = mavlink_msg_bms_data_get_LLIM_state(msg);
	bms_data->HLIM_state = mavlink_msg_bms_data_get_HLIM_state(msg);
	bms_data->state_of_chg = mavlink_msg_bms_data_get_state_of_chg(msg);
	bms_data->system_status = mavlink_msg_bms_data_get_system_status(msg);
	bms_data->mavlink_version = mavlink_msg_bms_data_get_mavlink_version(msg);
#else
	memcpy(bms_data, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_BMS_DATA_LEN);
#endif
}
