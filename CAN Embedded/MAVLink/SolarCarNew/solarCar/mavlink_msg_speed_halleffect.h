// MESSAGE SPEED_HALLEFFECT PACKING

#define MAVLINK_MSG_ID_SPEED_HALLEFFECT 155

typedef struct __mavlink_speed_halleffect_t
{
 uint16_t hes_RPM; ///<  the HES RPM
 uint16_t motor_RPM; ///<  the motordriver RPM
 uint8_t avg_speed; ///<  the average speed combined from both sensors 
 uint8_t hes_speed; ///<  the HE speed 
 uint8_t motor_speed; ///<  the motor driver speed 
 uint8_t flags; ///< status flags
} mavlink_speed_halleffect_t;

#define MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN 8
#define MAVLINK_MSG_ID_155_LEN 8

#define MAVLINK_MSG_ID_SPEED_HALLEFFECT_CRC 183
#define MAVLINK_MSG_ID_155_CRC 183



#define MAVLINK_MESSAGE_INFO_SPEED_HALLEFFECT { \
	"SPEED_HALLEFFECT", \
	6, \
	{  { "hes_RPM", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_speed_halleffect_t, hes_RPM) }, \
         { "motor_RPM", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_speed_halleffect_t, motor_RPM) }, \
         { "avg_speed", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_speed_halleffect_t, avg_speed) }, \
         { "hes_speed", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_speed_halleffect_t, hes_speed) }, \
         { "motor_speed", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_speed_halleffect_t, motor_speed) }, \
         { "flags", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_speed_halleffect_t, flags) }, \
         } \
}


/**
 * @brief Pack a speed_halleffect message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param avg_speed  the average speed combined from both sensors 
 * @param hes_speed  the HE speed 
 * @param hes_RPM  the HES RPM
 * @param motor_speed  the motor driver speed 
 * @param motor_RPM  the motordriver RPM
 * @param flags status flags
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speed_halleffect_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t avg_speed, uint8_t hes_speed, uint16_t hes_RPM, uint8_t motor_speed, uint16_t motor_RPM, uint8_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN];
	_mav_put_uint16_t(buf, 0, hes_RPM);
	_mav_put_uint16_t(buf, 2, motor_RPM);
	_mav_put_uint8_t(buf, 4, avg_speed);
	_mav_put_uint8_t(buf, 5, hes_speed);
	_mav_put_uint8_t(buf, 6, motor_speed);
	_mav_put_uint8_t(buf, 7, flags);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#else
	mavlink_speed_halleffect_t packet;
	packet.hes_RPM = hes_RPM;
	packet.motor_RPM = motor_RPM;
	packet.avg_speed = avg_speed;
	packet.hes_speed = hes_speed;
	packet.motor_speed = motor_speed;
	packet.flags = flags;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SPEED_HALLEFFECT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN, MAVLINK_MSG_ID_SPEED_HALLEFFECT_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#endif
}

/**
 * @brief Pack a speed_halleffect message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param avg_speed  the average speed combined from both sensors 
 * @param hes_speed  the HE speed 
 * @param hes_RPM  the HES RPM
 * @param motor_speed  the motor driver speed 
 * @param motor_RPM  the motordriver RPM
 * @param flags status flags
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speed_halleffect_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t avg_speed,uint8_t hes_speed,uint16_t hes_RPM,uint8_t motor_speed,uint16_t motor_RPM,uint8_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN];
	_mav_put_uint16_t(buf, 0, hes_RPM);
	_mav_put_uint16_t(buf, 2, motor_RPM);
	_mav_put_uint8_t(buf, 4, avg_speed);
	_mav_put_uint8_t(buf, 5, hes_speed);
	_mav_put_uint8_t(buf, 6, motor_speed);
	_mav_put_uint8_t(buf, 7, flags);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#else
	mavlink_speed_halleffect_t packet;
	packet.hes_RPM = hes_RPM;
	packet.motor_RPM = motor_RPM;
	packet.avg_speed = avg_speed;
	packet.hes_speed = hes_speed;
	packet.motor_speed = motor_speed;
	packet.flags = flags;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_SPEED_HALLEFFECT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN, MAVLINK_MSG_ID_SPEED_HALLEFFECT_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#endif
}

/**
 * @brief Encode a speed_halleffect struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param speed_halleffect C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speed_halleffect_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_speed_halleffect_t* speed_halleffect)
{
	return mavlink_msg_speed_halleffect_pack(system_id, component_id, msg, speed_halleffect->avg_speed, speed_halleffect->hes_speed, speed_halleffect->hes_RPM, speed_halleffect->motor_speed, speed_halleffect->motor_RPM, speed_halleffect->flags);
}

/**
 * @brief Encode a speed_halleffect struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param speed_halleffect C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speed_halleffect_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_speed_halleffect_t* speed_halleffect)
{
	return mavlink_msg_speed_halleffect_pack_chan(system_id, component_id, chan, msg, speed_halleffect->avg_speed, speed_halleffect->hes_speed, speed_halleffect->hes_RPM, speed_halleffect->motor_speed, speed_halleffect->motor_RPM, speed_halleffect->flags);
}

/**
 * @brief Send a speed_halleffect message
 * @param chan MAVLink channel to send the message
 *
 * @param avg_speed  the average speed combined from both sensors 
 * @param hes_speed  the HE speed 
 * @param hes_RPM  the HES RPM
 * @param motor_speed  the motor driver speed 
 * @param motor_RPM  the motordriver RPM
 * @param flags status flags
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_speed_halleffect_send(mavlink_channel_t chan, uint8_t avg_speed, uint8_t hes_speed, uint16_t hes_RPM, uint8_t motor_speed, uint16_t motor_RPM, uint8_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN];
	_mav_put_uint16_t(buf, 0, hes_RPM);
	_mav_put_uint16_t(buf, 2, motor_RPM);
	_mav_put_uint8_t(buf, 4, avg_speed);
	_mav_put_uint8_t(buf, 5, hes_speed);
	_mav_put_uint8_t(buf, 6, motor_speed);
	_mav_put_uint8_t(buf, 7, flags);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_HALLEFFECT, buf, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN, MAVLINK_MSG_ID_SPEED_HALLEFFECT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_HALLEFFECT, buf, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#endif
#else
	mavlink_speed_halleffect_t packet;
	packet.hes_RPM = hes_RPM;
	packet.motor_RPM = motor_RPM;
	packet.avg_speed = avg_speed;
	packet.hes_speed = hes_speed;
	packet.motor_speed = motor_speed;
	packet.flags = flags;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_HALLEFFECT, (const char *)&packet, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN, MAVLINK_MSG_ID_SPEED_HALLEFFECT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_HALLEFFECT, (const char *)&packet, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_speed_halleffect_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t avg_speed, uint8_t hes_speed, uint16_t hes_RPM, uint8_t motor_speed, uint16_t motor_RPM, uint8_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint16_t(buf, 0, hes_RPM);
	_mav_put_uint16_t(buf, 2, motor_RPM);
	_mav_put_uint8_t(buf, 4, avg_speed);
	_mav_put_uint8_t(buf, 5, hes_speed);
	_mav_put_uint8_t(buf, 6, motor_speed);
	_mav_put_uint8_t(buf, 7, flags);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_HALLEFFECT, buf, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN, MAVLINK_MSG_ID_SPEED_HALLEFFECT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_HALLEFFECT, buf, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#endif
#else
	mavlink_speed_halleffect_t *packet = (mavlink_speed_halleffect_t *)msgbuf;
	packet->hes_RPM = hes_RPM;
	packet->motor_RPM = motor_RPM;
	packet->avg_speed = avg_speed;
	packet->hes_speed = hes_speed;
	packet->motor_speed = motor_speed;
	packet->flags = flags;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_HALLEFFECT, (const char *)packet, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN, MAVLINK_MSG_ID_SPEED_HALLEFFECT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPEED_HALLEFFECT, (const char *)packet, MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE SPEED_HALLEFFECT UNPACKING


/**
 * @brief Get field avg_speed from speed_halleffect message
 *
 * @return  the average speed combined from both sensors 
 */
static inline uint8_t mavlink_msg_speed_halleffect_get_avg_speed(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field hes_speed from speed_halleffect message
 *
 * @return  the HE speed 
 */
static inline uint8_t mavlink_msg_speed_halleffect_get_hes_speed(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field hes_RPM from speed_halleffect message
 *
 * @return  the HES RPM
 */
static inline uint16_t mavlink_msg_speed_halleffect_get_hes_RPM(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field motor_speed from speed_halleffect message
 *
 * @return  the motor driver speed 
 */
static inline uint8_t mavlink_msg_speed_halleffect_get_motor_speed(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field motor_RPM from speed_halleffect message
 *
 * @return  the motordriver RPM
 */
static inline uint16_t mavlink_msg_speed_halleffect_get_motor_RPM(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field flags from speed_halleffect message
 *
 * @return status flags
 */
static inline uint8_t mavlink_msg_speed_halleffect_get_flags(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Decode a speed_halleffect message into a struct
 *
 * @param msg The message to decode
 * @param speed_halleffect C-struct to decode the message contents into
 */
static inline void mavlink_msg_speed_halleffect_decode(const mavlink_message_t* msg, mavlink_speed_halleffect_t* speed_halleffect)
{
#if MAVLINK_NEED_BYTE_SWAP
	speed_halleffect->hes_RPM = mavlink_msg_speed_halleffect_get_hes_RPM(msg);
	speed_halleffect->motor_RPM = mavlink_msg_speed_halleffect_get_motor_RPM(msg);
	speed_halleffect->avg_speed = mavlink_msg_speed_halleffect_get_avg_speed(msg);
	speed_halleffect->hes_speed = mavlink_msg_speed_halleffect_get_hes_speed(msg);
	speed_halleffect->motor_speed = mavlink_msg_speed_halleffect_get_motor_speed(msg);
	speed_halleffect->flags = mavlink_msg_speed_halleffect_get_flags(msg);
#else
	memcpy(speed_halleffect, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_SPEED_HALLEFFECT_LEN);
#endif
}
