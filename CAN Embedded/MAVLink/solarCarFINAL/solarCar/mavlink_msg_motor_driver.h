// MESSAGE MOTOR_DRIVER PACKING

#define MAVLINK_MSG_ID_MOTOR_DRIVER 155

typedef struct __mavlink_motor_driver_t
{
 uint8_t controller_temp; ///< value showing one of the 4 temperature ranges; '1' = below 85; '2' = 85-95; '3' = 95-105; '4' = over 105 
 uint8_t speed; ///< km/h reading obtained from converting motor RPM; 0-255km/h assumed.
} mavlink_motor_driver_t;

#define MAVLINK_MSG_ID_MOTOR_DRIVER_LEN 2
#define MAVLINK_MSG_ID_155_LEN 2

#define MAVLINK_MSG_ID_MOTOR_DRIVER_CRC 112
#define MAVLINK_MSG_ID_155_CRC 112



#define MAVLINK_MESSAGE_INFO_MOTOR_DRIVER { \
	"MOTOR_DRIVER", \
	2, \
	{  { "controller_temp", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_motor_driver_t, controller_temp) }, \
         { "speed", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_motor_driver_t, speed) }, \
         } \
}


/**
 * @brief Pack a motor_driver message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param controller_temp value showing one of the 4 temperature ranges; '1' = below 85; '2' = 85-95; '3' = 95-105; '4' = over 105 
 * @param speed km/h reading obtained from converting motor RPM; 0-255km/h assumed.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_driver_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t controller_temp, uint8_t speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MOTOR_DRIVER_LEN];
	_mav_put_uint8_t(buf, 0, controller_temp);
	_mav_put_uint8_t(buf, 1, speed);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#else
	mavlink_motor_driver_t packet;
	packet.controller_temp = controller_temp;
	packet.speed = speed;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MOTOR_DRIVER;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN, MAVLINK_MSG_ID_MOTOR_DRIVER_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#endif
}

/**
 * @brief Pack a motor_driver message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param controller_temp value showing one of the 4 temperature ranges; '1' = below 85; '2' = 85-95; '3' = 95-105; '4' = over 105 
 * @param speed km/h reading obtained from converting motor RPM; 0-255km/h assumed.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_driver_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t controller_temp,uint8_t speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MOTOR_DRIVER_LEN];
	_mav_put_uint8_t(buf, 0, controller_temp);
	_mav_put_uint8_t(buf, 1, speed);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#else
	mavlink_motor_driver_t packet;
	packet.controller_temp = controller_temp;
	packet.speed = speed;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MOTOR_DRIVER;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN, MAVLINK_MSG_ID_MOTOR_DRIVER_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#endif
}

/**
 * @brief Encode a motor_driver struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motor_driver C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_driver_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motor_driver_t* motor_driver)
{
	return mavlink_msg_motor_driver_pack(system_id, component_id, msg, motor_driver->controller_temp, motor_driver->speed);
}

/**
 * @brief Encode a motor_driver struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor_driver C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_driver_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motor_driver_t* motor_driver)
{
	return mavlink_msg_motor_driver_pack_chan(system_id, component_id, chan, msg, motor_driver->controller_temp, motor_driver->speed);
}

/**
 * @brief Send a motor_driver message
 * @param chan MAVLink channel to send the message
 *
 * @param controller_temp value showing one of the 4 temperature ranges; '1' = below 85; '2' = 85-95; '3' = 95-105; '4' = over 105 
 * @param speed km/h reading obtained from converting motor RPM; 0-255km/h assumed.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motor_driver_send(mavlink_channel_t chan, uint8_t controller_temp, uint8_t speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_MOTOR_DRIVER_LEN];
	_mav_put_uint8_t(buf, 0, controller_temp);
	_mav_put_uint8_t(buf, 1, speed);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_DRIVER, buf, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN, MAVLINK_MSG_ID_MOTOR_DRIVER_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_DRIVER, buf, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#endif
#else
	mavlink_motor_driver_t packet;
	packet.controller_temp = controller_temp;
	packet.speed = speed;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_DRIVER, (const char *)&packet, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN, MAVLINK_MSG_ID_MOTOR_DRIVER_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_DRIVER, (const char *)&packet, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_MOTOR_DRIVER_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motor_driver_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t controller_temp, uint8_t speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, controller_temp);
	_mav_put_uint8_t(buf, 1, speed);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_DRIVER, buf, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN, MAVLINK_MSG_ID_MOTOR_DRIVER_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_DRIVER, buf, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#endif
#else
	mavlink_motor_driver_t *packet = (mavlink_motor_driver_t *)msgbuf;
	packet->controller_temp = controller_temp;
	packet->speed = speed;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_DRIVER, (const char *)packet, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN, MAVLINK_MSG_ID_MOTOR_DRIVER_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_DRIVER, (const char *)packet, MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE MOTOR_DRIVER UNPACKING


/**
 * @brief Get field controller_temp from motor_driver message
 *
 * @return value showing one of the 4 temperature ranges; '1' = below 85; '2' = 85-95; '3' = 95-105; '4' = over 105 
 */
static inline uint8_t mavlink_msg_motor_driver_get_controller_temp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field speed from motor_driver message
 *
 * @return km/h reading obtained from converting motor RPM; 0-255km/h assumed.
 */
static inline uint8_t mavlink_msg_motor_driver_get_speed(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a motor_driver message into a struct
 *
 * @param msg The message to decode
 * @param motor_driver C-struct to decode the message contents into
 */
static inline void mavlink_msg_motor_driver_decode(const mavlink_message_t* msg, mavlink_motor_driver_t* motor_driver)
{
#if MAVLINK_NEED_BYTE_SWAP
	motor_driver->controller_temp = mavlink_msg_motor_driver_get_controller_temp(msg);
	motor_driver->speed = mavlink_msg_motor_driver_get_speed(msg);
#else
	memcpy(motor_driver, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_MOTOR_DRIVER_LEN);
#endif
}
