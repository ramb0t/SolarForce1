// MESSAGE MPPT3_DATA PACKING

#define MAVLINK_MSG_ID_MPPT3_DATA 153

typedef struct __mavlink_mppt3_data_t
{
 uint16_t voltage_in; ///< Input voltage to MPPT (0-65535V)
 uint16_t current_in; ///< Input current to MPPT (0mA-6.5535kA)
 uint16_t voltage_out; ///< output voltage from MPPT (0mA-6.5535kA)
 uint8_t ambient_temp; ///< Ambient temperature
 uint8_t status; ///< status flags
} mavlink_mppt3_data_t;

#define MAVLINK_MSG_ID_MPPT3_DATA_LEN 8
#define MAVLINK_MSG_ID_153_LEN 8

#define MAVLINK_MSG_ID_MPPT3_DATA_CRC 97
#define MAVLINK_MSG_ID_153_CRC 97



#define MAVLINK_MESSAGE_INFO_MPPT3_DATA { \
	"MPPT3_DATA", \
	5, \
	{  { "voltage_in", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_mppt3_data_t, voltage_in) }, \
         { "current_in", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_mppt3_data_t, current_in) }, \
         { "voltage_out", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_mppt3_data_t, voltage_out) }, \
         { "ambient_temp", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_mppt3_data_t, ambient_temp) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_mppt3_data_t, status) }, \
         } \
}


/**
 * @brief Pack a mppt3_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param voltage_in Input voltage to MPPT (0-65535V)
 * @param current_in Input current to MPPT (0mA-6.5535kA)
 * @param voltage_out output voltage from MPPT (0mA-6.5535kA)
 * @param ambient_temp Ambient temperature
 * @param status status flags
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mppt3_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint16_t voltage_in, uint16_t current_in, uint16_t voltage_out, uint8_t ambient_temp, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MPPT3_DATA_LEN];
	_mav_put_uint16_t(buf, 0, voltage_in);
	_mav_put_uint16_t(buf, 2, current_in);
	_mav_put_uint16_t(buf, 4, voltage_out);
	_mav_put_uint8_t(buf, 6, ambient_temp);
	_mav_put_uint8_t(buf, 7, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#else
	mavlink_mppt3_data_t packet;
	packet.voltage_in = voltage_in;
	packet.current_in = current_in;
	packet.voltage_out = voltage_out;
	packet.ambient_temp = ambient_temp;
	packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MPPT3_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MPPT3_DATA_LEN, MAVLINK_MSG_ID_MPPT3_DATA_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#endif
}

/**
 * @brief Pack a mppt3_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param voltage_in Input voltage to MPPT (0-65535V)
 * @param current_in Input current to MPPT (0mA-6.5535kA)
 * @param voltage_out output voltage from MPPT (0mA-6.5535kA)
 * @param ambient_temp Ambient temperature
 * @param status status flags
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mppt3_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint16_t voltage_in,uint16_t current_in,uint16_t voltage_out,uint8_t ambient_temp,uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MPPT3_DATA_LEN];
	_mav_put_uint16_t(buf, 0, voltage_in);
	_mav_put_uint16_t(buf, 2, current_in);
	_mav_put_uint16_t(buf, 4, voltage_out);
	_mav_put_uint8_t(buf, 6, ambient_temp);
	_mav_put_uint8_t(buf, 7, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#else
	mavlink_mppt3_data_t packet;
	packet.voltage_in = voltage_in;
	packet.current_in = current_in;
	packet.voltage_out = voltage_out;
	packet.ambient_temp = ambient_temp;
	packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MPPT3_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MPPT3_DATA_LEN, MAVLINK_MSG_ID_MPPT3_DATA_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#endif
}

/**
 * @brief Encode a mppt3_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mppt3_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mppt3_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mppt3_data_t* mppt3_data)
{
	return mavlink_msg_mppt3_data_pack(system_id, component_id, msg, mppt3_data->voltage_in, mppt3_data->current_in, mppt3_data->voltage_out, mppt3_data->ambient_temp, mppt3_data->status);
}

/**
 * @brief Encode a mppt3_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mppt3_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mppt3_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mppt3_data_t* mppt3_data)
{
	return mavlink_msg_mppt3_data_pack_chan(system_id, component_id, chan, msg, mppt3_data->voltage_in, mppt3_data->current_in, mppt3_data->voltage_out, mppt3_data->ambient_temp, mppt3_data->status);
}

/**
 * @brief Send a mppt3_data message
 * @param chan MAVLink channel to send the message
 *
 * @param voltage_in Input voltage to MPPT (0-65535V)
 * @param current_in Input current to MPPT (0mA-6.5535kA)
 * @param voltage_out output voltage from MPPT (0mA-6.5535kA)
 * @param ambient_temp Ambient temperature
 * @param status status flags
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mppt3_data_send(mavlink_channel_t chan, uint16_t voltage_in, uint16_t current_in, uint16_t voltage_out, uint8_t ambient_temp, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MPPT3_DATA_LEN];
	_mav_put_uint16_t(buf, 0, voltage_in);
	_mav_put_uint16_t(buf, 2, current_in);
	_mav_put_uint16_t(buf, 4, voltage_out);
	_mav_put_uint8_t(buf, 6, ambient_temp);
	_mav_put_uint8_t(buf, 7, status);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT3_DATA, buf, MAVLINK_MSG_ID_MPPT3_DATA_LEN, MAVLINK_MSG_ID_MPPT3_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT3_DATA, buf, MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#endif
#else
	mavlink_mppt3_data_t packet;
	packet.voltage_in = voltage_in;
	packet.current_in = current_in;
	packet.voltage_out = voltage_out;
	packet.ambient_temp = ambient_temp;
	packet.status = status;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT3_DATA, (const char *)&packet, MAVLINK_MSG_ID_MPPT3_DATA_LEN, MAVLINK_MSG_ID_MPPT3_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT3_DATA, (const char *)&packet, MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_MPPT3_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mppt3_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t voltage_in, uint16_t current_in, uint16_t voltage_out, uint8_t ambient_temp, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint16_t(buf, 0, voltage_in);
	_mav_put_uint16_t(buf, 2, current_in);
	_mav_put_uint16_t(buf, 4, voltage_out);
	_mav_put_uint8_t(buf, 6, ambient_temp);
	_mav_put_uint8_t(buf, 7, status);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT3_DATA, buf, MAVLINK_MSG_ID_MPPT3_DATA_LEN, MAVLINK_MSG_ID_MPPT3_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT3_DATA, buf, MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#endif
#else
	mavlink_mppt3_data_t *packet = (mavlink_mppt3_data_t *)msgbuf;
	packet->voltage_in = voltage_in;
	packet->current_in = current_in;
	packet->voltage_out = voltage_out;
	packet->ambient_temp = ambient_temp;
	packet->status = status;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT3_DATA, (const char *)packet, MAVLINK_MSG_ID_MPPT3_DATA_LEN, MAVLINK_MSG_ID_MPPT3_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT3_DATA, (const char *)packet, MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE MPPT3_DATA UNPACKING


/**
 * @brief Get field voltage_in from mppt3_data message
 *
 * @return Input voltage to MPPT (0-65535V)
 */
static inline uint16_t mavlink_msg_mppt3_data_get_voltage_in(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field current_in from mppt3_data message
 *
 * @return Input current to MPPT (0mA-6.5535kA)
 */
static inline uint16_t mavlink_msg_mppt3_data_get_current_in(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field voltage_out from mppt3_data message
 *
 * @return output voltage from MPPT (0mA-6.5535kA)
 */
static inline uint16_t mavlink_msg_mppt3_data_get_voltage_out(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field ambient_temp from mppt3_data message
 *
 * @return Ambient temperature
 */
static inline uint8_t mavlink_msg_mppt3_data_get_ambient_temp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field status from mppt3_data message
 *
 * @return status flags
 */
static inline uint8_t mavlink_msg_mppt3_data_get_status(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Decode a mppt3_data message into a struct
 *
 * @param msg The message to decode
 * @param mppt3_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_mppt3_data_decode(const mavlink_message_t* msg, mavlink_mppt3_data_t* mppt3_data)
{
#if MAVLINK_NEED_BYTE_SWAP
	mppt3_data->voltage_in = mavlink_msg_mppt3_data_get_voltage_in(msg);
	mppt3_data->current_in = mavlink_msg_mppt3_data_get_current_in(msg);
	mppt3_data->voltage_out = mavlink_msg_mppt3_data_get_voltage_out(msg);
	mppt3_data->ambient_temp = mavlink_msg_mppt3_data_get_ambient_temp(msg);
	mppt3_data->status = mavlink_msg_mppt3_data_get_status(msg);
#else
	memcpy(mppt3_data, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_MPPT3_DATA_LEN);
#endif
}
