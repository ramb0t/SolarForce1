// MESSAGE MPPT4_DATA PACKING

#define MAVLINK_MSG_ID_MPPT4_DATA 154

typedef struct __mavlink_mppt4_data_t
{
 uint16_t voltage_in; ///< Input voltage to MPPT (0-65535V)
 uint16_t current_in; ///< Input current to MPPT (0mA-6.5535kA)
 uint8_t overtemp; ///< Flag to indicate the MPPTs are over temperature ('1' = over temp; '0' = OK)
 uint8_t undervolt; ///< Flag to indicate the MPPTs are under voltage ('1' = over temp; '0' = OK)
} mavlink_mppt4_data_t;

#define MAVLINK_MSG_ID_MPPT4_DATA_LEN 6
#define MAVLINK_MSG_ID_154_LEN 6

#define MAVLINK_MSG_ID_MPPT4_DATA_CRC 136
#define MAVLINK_MSG_ID_154_CRC 136



#define MAVLINK_MESSAGE_INFO_MPPT4_DATA { \
	"MPPT4_DATA", \
	4, \
	{  { "voltage_in", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_mppt4_data_t, voltage_in) }, \
         { "current_in", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_mppt4_data_t, current_in) }, \
         { "overtemp", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_mppt4_data_t, overtemp) }, \
         { "undervolt", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_mppt4_data_t, undervolt) }, \
         } \
}


/**
 * @brief Pack a mppt4_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param voltage_in Input voltage to MPPT (0-65535V)
 * @param current_in Input current to MPPT (0mA-6.5535kA)
 * @param overtemp Flag to indicate the MPPTs are over temperature ('1' = over temp; '0' = OK)
 * @param undervolt Flag to indicate the MPPTs are under voltage ('1' = over temp; '0' = OK)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mppt4_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint16_t voltage_in, uint16_t current_in, uint8_t overtemp, uint8_t undervolt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MPPT4_DATA_LEN];
	_mav_put_uint16_t(buf, 0, voltage_in);
	_mav_put_uint16_t(buf, 2, current_in);
	_mav_put_uint8_t(buf, 4, overtemp);
	_mav_put_uint8_t(buf, 5, undervolt);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#else
	mavlink_mppt4_data_t packet;
	packet.voltage_in = voltage_in;
	packet.current_in = current_in;
	packet.overtemp = overtemp;
	packet.undervolt = undervolt;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MPPT4_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MPPT4_DATA_LEN, MAVLINK_MSG_ID_MPPT4_DATA_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#endif
}

/**
 * @brief Pack a mppt4_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param voltage_in Input voltage to MPPT (0-65535V)
 * @param current_in Input current to MPPT (0mA-6.5535kA)
 * @param overtemp Flag to indicate the MPPTs are over temperature ('1' = over temp; '0' = OK)
 * @param undervolt Flag to indicate the MPPTs are under voltage ('1' = over temp; '0' = OK)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mppt4_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint16_t voltage_in,uint16_t current_in,uint8_t overtemp,uint8_t undervolt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MPPT4_DATA_LEN];
	_mav_put_uint16_t(buf, 0, voltage_in);
	_mav_put_uint16_t(buf, 2, current_in);
	_mav_put_uint8_t(buf, 4, overtemp);
	_mav_put_uint8_t(buf, 5, undervolt);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#else
	mavlink_mppt4_data_t packet;
	packet.voltage_in = voltage_in;
	packet.current_in = current_in;
	packet.overtemp = overtemp;
	packet.undervolt = undervolt;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MPPT4_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MPPT4_DATA_LEN, MAVLINK_MSG_ID_MPPT4_DATA_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#endif
}

/**
 * @brief Encode a mppt4_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mppt4_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mppt4_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mppt4_data_t* mppt4_data)
{
	return mavlink_msg_mppt4_data_pack(system_id, component_id, msg, mppt4_data->voltage_in, mppt4_data->current_in, mppt4_data->overtemp, mppt4_data->undervolt);
}

/**
 * @brief Encode a mppt4_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mppt4_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mppt4_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mppt4_data_t* mppt4_data)
{
	return mavlink_msg_mppt4_data_pack_chan(system_id, component_id, chan, msg, mppt4_data->voltage_in, mppt4_data->current_in, mppt4_data->overtemp, mppt4_data->undervolt);
}

/**
 * @brief Send a mppt4_data message
 * @param chan MAVLink channel to send the message
 *
 * @param voltage_in Input voltage to MPPT (0-65535V)
 * @param current_in Input current to MPPT (0mA-6.5535kA)
 * @param overtemp Flag to indicate the MPPTs are over temperature ('1' = over temp; '0' = OK)
 * @param undervolt Flag to indicate the MPPTs are under voltage ('1' = over temp; '0' = OK)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mppt4_data_send(mavlink_channel_t chan, uint16_t voltage_in, uint16_t current_in, uint8_t overtemp, uint8_t undervolt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MPPT4_DATA_LEN];
	_mav_put_uint16_t(buf, 0, voltage_in);
	_mav_put_uint16_t(buf, 2, current_in);
	_mav_put_uint8_t(buf, 4, overtemp);
	_mav_put_uint8_t(buf, 5, undervolt);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT4_DATA, buf, MAVLINK_MSG_ID_MPPT4_DATA_LEN, MAVLINK_MSG_ID_MPPT4_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT4_DATA, buf, MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#endif
#else
	mavlink_mppt4_data_t packet;
	packet.voltage_in = voltage_in;
	packet.current_in = current_in;
	packet.overtemp = overtemp;
	packet.undervolt = undervolt;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT4_DATA, (const char *)&packet, MAVLINK_MSG_ID_MPPT4_DATA_LEN, MAVLINK_MSG_ID_MPPT4_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT4_DATA, (const char *)&packet, MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_MPPT4_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mppt4_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t voltage_in, uint16_t current_in, uint8_t overtemp, uint8_t undervolt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint16_t(buf, 0, voltage_in);
	_mav_put_uint16_t(buf, 2, current_in);
	_mav_put_uint8_t(buf, 4, overtemp);
	_mav_put_uint8_t(buf, 5, undervolt);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT4_DATA, buf, MAVLINK_MSG_ID_MPPT4_DATA_LEN, MAVLINK_MSG_ID_MPPT4_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT4_DATA, buf, MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#endif
#else
	mavlink_mppt4_data_t *packet = (mavlink_mppt4_data_t *)msgbuf;
	packet->voltage_in = voltage_in;
	packet->current_in = current_in;
	packet->overtemp = overtemp;
	packet->undervolt = undervolt;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT4_DATA, (const char *)packet, MAVLINK_MSG_ID_MPPT4_DATA_LEN, MAVLINK_MSG_ID_MPPT4_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MPPT4_DATA, (const char *)packet, MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE MPPT4_DATA UNPACKING


/**
 * @brief Get field voltage_in from mppt4_data message
 *
 * @return Input voltage to MPPT (0-65535V)
 */
static inline uint16_t mavlink_msg_mppt4_data_get_voltage_in(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field current_in from mppt4_data message
 *
 * @return Input current to MPPT (0mA-6.5535kA)
 */
static inline uint16_t mavlink_msg_mppt4_data_get_current_in(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field overtemp from mppt4_data message
 *
 * @return Flag to indicate the MPPTs are over temperature ('1' = over temp; '0' = OK)
 */
static inline uint8_t mavlink_msg_mppt4_data_get_overtemp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field undervolt from mppt4_data message
 *
 * @return Flag to indicate the MPPTs are under voltage ('1' = over temp; '0' = OK)
 */
static inline uint8_t mavlink_msg_mppt4_data_get_undervolt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Decode a mppt4_data message into a struct
 *
 * @param msg The message to decode
 * @param mppt4_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_mppt4_data_decode(const mavlink_message_t* msg, mavlink_mppt4_data_t* mppt4_data)
{
#if MAVLINK_NEED_BYTE_SWAP
	mppt4_data->voltage_in = mavlink_msg_mppt4_data_get_voltage_in(msg);
	mppt4_data->current_in = mavlink_msg_mppt4_data_get_current_in(msg);
	mppt4_data->overtemp = mavlink_msg_mppt4_data_get_overtemp(msg);
	mppt4_data->undervolt = mavlink_msg_mppt4_data_get_undervolt(msg);
#else
	memcpy(mppt4_data, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_MPPT4_DATA_LEN);
#endif
}
