// MESSAGE ACCELO_GYRO PACKING

#define MAVLINK_MSG_ID_ACCELO_GYRO 157

typedef struct __mavlink_accelo_gyro_t
{
 int16_t gyro_x; ///< MPU6050 output value for x-orientation
 int16_t gyro_y; ///< MPU6050 output value for y-orientation
 int16_t gyro_z; ///< MPU6050 output value for z-orientation
 int16_t accel_x; ///< MPU6050 output value for x-acceleration
 int16_t accel_y; ///< MPU6050 output value for y-acceleration
 int16_t accel_z; ///< MPU6050 output value for z-acceleration
} mavlink_accelo_gyro_t;

#define MAVLINK_MSG_ID_ACCELO_GYRO_LEN 12
#define MAVLINK_MSG_ID_157_LEN 12

#define MAVLINK_MSG_ID_ACCELO_GYRO_CRC 81
#define MAVLINK_MSG_ID_157_CRC 81



#define MAVLINK_MESSAGE_INFO_ACCELO_GYRO { \
	"ACCELO_GYRO", \
	6, \
	{  { "gyro_x", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_accelo_gyro_t, gyro_x) }, \
         { "gyro_y", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_accelo_gyro_t, gyro_y) }, \
         { "gyro_z", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_accelo_gyro_t, gyro_z) }, \
         { "accel_x", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_accelo_gyro_t, accel_x) }, \
         { "accel_y", NULL, MAVLINK_TYPE_INT16_T, 0, 8, offsetof(mavlink_accelo_gyro_t, accel_y) }, \
         { "accel_z", NULL, MAVLINK_TYPE_INT16_T, 0, 10, offsetof(mavlink_accelo_gyro_t, accel_z) }, \
         } \
}


/**
 * @brief Pack a accelo_gyro message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param gyro_x MPU6050 output value for x-orientation
 * @param gyro_y MPU6050 output value for y-orientation
 * @param gyro_z MPU6050 output value for z-orientation
 * @param accel_x MPU6050 output value for x-acceleration
 * @param accel_y MPU6050 output value for y-acceleration
 * @param accel_z MPU6050 output value for z-acceleration
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_accelo_gyro_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       int16_t gyro_x, int16_t gyro_y, int16_t gyro_z, int16_t accel_x, int16_t accel_y, int16_t accel_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACCELO_GYRO_LEN];
	_mav_put_int16_t(buf, 0, gyro_x);
	_mav_put_int16_t(buf, 2, gyro_y);
	_mav_put_int16_t(buf, 4, gyro_z);
	_mav_put_int16_t(buf, 6, accel_x);
	_mav_put_int16_t(buf, 8, accel_y);
	_mav_put_int16_t(buf, 10, accel_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#else
	mavlink_accelo_gyro_t packet;
	packet.gyro_x = gyro_x;
	packet.gyro_y = gyro_y;
	packet.gyro_z = gyro_z;
	packet.accel_x = accel_x;
	packet.accel_y = accel_y;
	packet.accel_z = accel_z;

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
 * @param gyro_x MPU6050 output value for x-orientation
 * @param gyro_y MPU6050 output value for y-orientation
 * @param gyro_z MPU6050 output value for z-orientation
 * @param accel_x MPU6050 output value for x-acceleration
 * @param accel_y MPU6050 output value for y-acceleration
 * @param accel_z MPU6050 output value for z-acceleration
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_accelo_gyro_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           int16_t gyro_x,int16_t gyro_y,int16_t gyro_z,int16_t accel_x,int16_t accel_y,int16_t accel_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACCELO_GYRO_LEN];
	_mav_put_int16_t(buf, 0, gyro_x);
	_mav_put_int16_t(buf, 2, gyro_y);
	_mav_put_int16_t(buf, 4, gyro_z);
	_mav_put_int16_t(buf, 6, accel_x);
	_mav_put_int16_t(buf, 8, accel_y);
	_mav_put_int16_t(buf, 10, accel_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#else
	mavlink_accelo_gyro_t packet;
	packet.gyro_x = gyro_x;
	packet.gyro_y = gyro_y;
	packet.gyro_z = gyro_z;
	packet.accel_x = accel_x;
	packet.accel_y = accel_y;
	packet.accel_z = accel_z;

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
	return mavlink_msg_accelo_gyro_pack(system_id, component_id, msg, accelo_gyro->gyro_x, accelo_gyro->gyro_y, accelo_gyro->gyro_z, accelo_gyro->accel_x, accelo_gyro->accel_y, accelo_gyro->accel_z);
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
	return mavlink_msg_accelo_gyro_pack_chan(system_id, component_id, chan, msg, accelo_gyro->gyro_x, accelo_gyro->gyro_y, accelo_gyro->gyro_z, accelo_gyro->accel_x, accelo_gyro->accel_y, accelo_gyro->accel_z);
}

/**
 * @brief Send a accelo_gyro message
 * @param chan MAVLink channel to send the message
 *
 * @param gyro_x MPU6050 output value for x-orientation
 * @param gyro_y MPU6050 output value for y-orientation
 * @param gyro_z MPU6050 output value for z-orientation
 * @param accel_x MPU6050 output value for x-acceleration
 * @param accel_y MPU6050 output value for y-acceleration
 * @param accel_z MPU6050 output value for z-acceleration
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_accelo_gyro_send(mavlink_channel_t chan, int16_t gyro_x, int16_t gyro_y, int16_t gyro_z, int16_t accel_x, int16_t accel_y, int16_t accel_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ACCELO_GYRO_LEN];
	_mav_put_int16_t(buf, 0, gyro_x);
	_mav_put_int16_t(buf, 2, gyro_y);
	_mav_put_int16_t(buf, 4, gyro_z);
	_mav_put_int16_t(buf, 6, accel_x);
	_mav_put_int16_t(buf, 8, accel_y);
	_mav_put_int16_t(buf, 10, accel_z);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN, MAVLINK_MSG_ID_ACCELO_GYRO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif
#else
	mavlink_accelo_gyro_t packet;
	packet.gyro_x = gyro_x;
	packet.gyro_y = gyro_y;
	packet.gyro_z = gyro_z;
	packet.accel_x = accel_x;
	packet.accel_y = accel_y;
	packet.accel_z = accel_z;

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
static inline void mavlink_msg_accelo_gyro_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int16_t gyro_x, int16_t gyro_y, int16_t gyro_z, int16_t accel_x, int16_t accel_y, int16_t accel_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_int16_t(buf, 0, gyro_x);
	_mav_put_int16_t(buf, 2, gyro_y);
	_mav_put_int16_t(buf, 4, gyro_z);
	_mav_put_int16_t(buf, 6, accel_x);
	_mav_put_int16_t(buf, 8, accel_y);
	_mav_put_int16_t(buf, 10, accel_z);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN, MAVLINK_MSG_ID_ACCELO_GYRO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ACCELO_GYRO, buf, MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif
#else
	mavlink_accelo_gyro_t *packet = (mavlink_accelo_gyro_t *)msgbuf;
	packet->gyro_x = gyro_x;
	packet->gyro_y = gyro_y;
	packet->gyro_z = gyro_z;
	packet->accel_x = accel_x;
	packet->accel_y = accel_y;
	packet->accel_z = accel_z;

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
 * @brief Get field gyro_x from accelo_gyro message
 *
 * @return MPU6050 output value for x-orientation
 */
static inline int16_t mavlink_msg_accelo_gyro_get_gyro_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field gyro_y from accelo_gyro message
 *
 * @return MPU6050 output value for y-orientation
 */
static inline int16_t mavlink_msg_accelo_gyro_get_gyro_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field gyro_z from accelo_gyro message
 *
 * @return MPU6050 output value for z-orientation
 */
static inline int16_t mavlink_msg_accelo_gyro_get_gyro_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Get field accel_x from accelo_gyro message
 *
 * @return MPU6050 output value for x-acceleration
 */
static inline int16_t mavlink_msg_accelo_gyro_get_accel_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  6);
}

/**
 * @brief Get field accel_y from accelo_gyro message
 *
 * @return MPU6050 output value for y-acceleration
 */
static inline int16_t mavlink_msg_accelo_gyro_get_accel_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  8);
}

/**
 * @brief Get field accel_z from accelo_gyro message
 *
 * @return MPU6050 output value for z-acceleration
 */
static inline int16_t mavlink_msg_accelo_gyro_get_accel_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  10);
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
	accelo_gyro->gyro_x = mavlink_msg_accelo_gyro_get_gyro_x(msg);
	accelo_gyro->gyro_y = mavlink_msg_accelo_gyro_get_gyro_y(msg);
	accelo_gyro->gyro_z = mavlink_msg_accelo_gyro_get_gyro_z(msg);
	accelo_gyro->accel_x = mavlink_msg_accelo_gyro_get_accel_x(msg);
	accelo_gyro->accel_y = mavlink_msg_accelo_gyro_get_accel_y(msg);
	accelo_gyro->accel_z = mavlink_msg_accelo_gyro_get_accel_z(msg);
#else
	memcpy(accelo_gyro, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ACCELO_GYRO_LEN);
#endif
}
