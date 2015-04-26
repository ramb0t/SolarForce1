// MESSAGE ACCELO_GYRO PACKING

#define MAVLINK_MSG_ID_ACCELO_GYRO 157

typedef struct __mavlink_accelo_gyro_t
{
 int8_t acceleration; ///< MPU6050 output value for acceleration in m.s^-2 (-127->127)
 int8_t incline; ///< MPU6050 output value for inclination in degrees signed (-127->127)
} mavlink_accelo_gyro_t;

#define MAVLINK_MSG_ID_ACCELO_GYRO_LEN 2
#define MAVLINK_MSG_ID_157_LEN 2

#define MAVLINK_MSG_ID_ACCELO_GYRO_CRC 217
#define MAVLINK_MSG_ID_157_CRC 217



#define MAVLINK_MESSAGE_INFO_ACCELO_GYRO { \
	"ACCELO_GYRO", \
	2, \
	{  { "acceleration", NULL, MAVLINK_TYPE_INT8_T, 0, 0, offsetof(mavlink_accelo_gyro_t, acceleration) }, \
         { "incline", NULL, MAVLINK_TYPE_INT8_T, 0, 1, offsetof(mavlink_accelo_gyro_t, incline) }, \
         } \
}


/**
 * @brief Pack a accelo_gyro message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param acceleration MPU6050 output value for acceleration in m.s^-2 (-127->127)
 * @param incline MPU6050 output value for inclination in degrees signed (-127->127)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_accelo_gyro_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       int8_t acceleration, int8_t incline)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACCELO_GYRO_LEN];
	_mav_put_int8_t(buf, 0, acceleration);
	_mav_put_int8_t(buf, 1, incline);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#else
	mavlink_accelo_gyro_t packet;
	packet.acceleration = acceleration;
	packet.incline = incline;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACCELO_GYRO;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACCELO_GYRO_LEN, MAVLINK_MSG_ID_ACCELO_GYRO_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif
}

/**
 * @brief Pack a accelo_gyro message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param acceleration MPU6050 output value for acceleration in m.s^-2 (-127->127)
 * @param incline MPU6050 output value for inclination in degrees signed (-127->127)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_accelo_gyro_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           int8_t acceleration,int8_t incline)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACCELO_GYRO_LEN];
	_mav_put_int8_t(buf, 0, acceleration);
	_mav_put_int8_t(buf, 1, incline);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#else
	mavlink_accelo_gyro_t packet;
	packet.acceleration = acceleration;
	packet.incline = incline;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ACCELO_GYRO;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACCELO_GYRO_LEN, MAVLINK_MSG_ID_ACCELO_GYRO_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif
}

/**
 * @brief Encode a accelo_gyro struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param accelo_gyro C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_accelo_gyro_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_accelo_gyro_t* accelo_gyro)
{
	return mavlink_msg_accelo_gyro_pack(system_id, component_id, msg, accelo_gyro->acceleration, accelo_gyro->incline);
}

/**
 * @brief Encode a accelo_gyro struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param accelo_gyro C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_accelo_gyro_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_accelo_gyro_t* accelo_gyro)
{
	return mavlink_msg_accelo_gyro_pack_chan(system_id, component_id, chan, msg, accelo_gyro->acceleration, accelo_gyro->incline);
}

/**
 * @brief Send a accelo_gyro message
 * @param chan MAVLink channel to send the message
 *
 * @param acceleration MPU6050 output value for acceleration in m.s^-2 (-127->127)
 * @param incline MPU6050 output value for inclination in degrees signed (-127->127)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_accelo_gyro_send(mavlink_channel_t chan, int8_t acceleration, int8_t incline)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACCELO_GYRO_LEN];
	_mav_put_int8_t(buf, 0, acceleration);
	_mav_put_int8_t(buf, 1, incline);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN, MAVLINK_MSG_ID_ACCELO_GYRO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif
#else
	mavlink_accelo_gyro_t packet;
	packet.acceleration = acceleration;
	packet.incline = incline;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, (const char *)&packet, MAVLINK_MSG_ID_ACCELO_GYRO_LEN, MAVLINK_MSG_ID_ACCELO_GYRO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, (const char *)&packet, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_ACCELO_GYRO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_accelo_gyro_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int8_t acceleration, int8_t incline)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_int8_t(buf, 0, acceleration);
	_mav_put_int8_t(buf, 1, incline);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN, MAVLINK_MSG_ID_ACCELO_GYRO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif
#else
	mavlink_accelo_gyro_t *packet = (mavlink_accelo_gyro_t *)msgbuf;
	packet->acceleration = acceleration;
	packet->incline = incline;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, (const char *)packet, MAVLINK_MSG_ID_ACCELO_GYRO_LEN, MAVLINK_MSG_ID_ACCELO_GYRO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, (const char *)packet, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE ACCELO_GYRO UNPACKING


/**
 * @brief Get field acceleration from accelo_gyro message
 *
 * @return MPU6050 output value for acceleration in m.s^-2 (-127->127)
 */
static inline int8_t mavlink_msg_accelo_gyro_get_acceleration(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  0);
}

/**
 * @brief Get field incline from accelo_gyro message
 *
 * @return MPU6050 output value for inclination in degrees signed (-127->127)
 */
static inline int8_t mavlink_msg_accelo_gyro_get_incline(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int8_t(msg,  1);
}

/**
 * @brief Decode a accelo_gyro message into a struct
 *
 * @param msg The message to decode
 * @param accelo_gyro C-struct to decode the message contents into
 */
static inline void mavlink_msg_accelo_gyro_decode(const mavlink_message_t* msg, mavlink_accelo_gyro_t* accelo_gyro)
{
#if MAVLINK_NEED_BYTE_SWAP
	accelo_gyro->acceleration = mavlink_msg_accelo_gyro_get_acceleration(msg);
	accelo_gyro->incline = mavlink_msg_accelo_gyro_get_incline(msg);
#else
	memcpy(accelo_gyro, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif
}
