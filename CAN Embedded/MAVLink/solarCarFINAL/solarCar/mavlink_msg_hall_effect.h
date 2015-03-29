// MESSAGE HALL_EFFECT PACKING

#define MAVLINK_MSG_ID_HALL_EFFECT 158

typedef struct __mavlink_hall_effect_t
{
 float speed; ///< Hall Effect sensor averaged speed reading in km/h
 uint8_t left_magnet; ///< flag for presence of left wheel Hall Effect magnet; '1' = present, '0' = missing
 uint8_t right_magnet; ///< flag for presence of right wheel Hall Effect magnet; '1' = present, '0' = missing
} mavlink_hall_effect_t;

#define MAVLINK_MSG_ID_HALL_EFFECT_LEN 6
#define MAVLINK_MSG_ID_158_LEN 6

#define MAVLINK_MSG_ID_HALL_EFFECT_CRC 200
#define MAVLINK_MSG_ID_158_CRC 200



#define MAVLINK_MESSAGE_INFO_HALL_EFFECT { \
	"HALL_EFFECT", \
	3, \
	{  { "speed", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_hall_effect_t, speed) }, \
         { "left_magnet", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_hall_effect_t, left_magnet) }, \
         { "right_magnet", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_hall_effect_t, right_magnet) }, \
         } \
}


/**
 * @brief Pack a hall_effect message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param speed Hall Effect sensor averaged speed reading in km/h
 * @param left_magnet flag for presence of left wheel Hall Effect magnet; '1' = present, '0' = missing
 * @param right_magnet flag for presence of right wheel Hall Effect magnet; '1' = present, '0' = missing
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hall_effect_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float speed, uint8_t left_magnet, uint8_t right_magnet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_HALL_EFFECT_LEN];
	_mav_put_float(buf, 0, speed);
	_mav_put_uint8_t(buf, 4, left_magnet);
	_mav_put_uint8_t(buf, 5, right_magnet);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#else
	mavlink_hall_effect_t packet;
	packet.speed = speed;
	packet.left_magnet = left_magnet;
	packet.right_magnet = right_magnet;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_HALL_EFFECT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HALL_EFFECT_LEN, MAVLINK_MSG_ID_HALL_EFFECT_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#endif
}

/**
 * @brief Pack a hall_effect message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param speed Hall Effect sensor averaged speed reading in km/h
 * @param left_magnet flag for presence of left wheel Hall Effect magnet; '1' = present, '0' = missing
 * @param right_magnet flag for presence of right wheel Hall Effect magnet; '1' = present, '0' = missing
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hall_effect_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float speed,uint8_t left_magnet,uint8_t right_magnet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_HALL_EFFECT_LEN];
	_mav_put_float(buf, 0, speed);
	_mav_put_uint8_t(buf, 4, left_magnet);
	_mav_put_uint8_t(buf, 5, right_magnet);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#else
	mavlink_hall_effect_t packet;
	packet.speed = speed;
	packet.left_magnet = left_magnet;
	packet.right_magnet = right_magnet;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_HALL_EFFECT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HALL_EFFECT_LEN, MAVLINK_MSG_ID_HALL_EFFECT_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#endif
}

/**
 * @brief Encode a hall_effect struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param hall_effect C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hall_effect_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_hall_effect_t* hall_effect)
{
	return mavlink_msg_hall_effect_pack(system_id, component_id, msg, hall_effect->speed, hall_effect->left_magnet, hall_effect->right_magnet);
}

/**
 * @brief Encode a hall_effect struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param hall_effect C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hall_effect_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_hall_effect_t* hall_effect)
{
	return mavlink_msg_hall_effect_pack_chan(system_id, component_id, chan, msg, hall_effect->speed, hall_effect->left_magnet, hall_effect->right_magnet);
}

/**
 * @brief Send a hall_effect message
 * @param chan MAVLink channel to send the message
 *
 * @param speed Hall Effect sensor averaged speed reading in km/h
 * @param left_magnet flag for presence of left wheel Hall Effect magnet; '1' = present, '0' = missing
 * @param right_magnet flag for presence of right wheel Hall Effect magnet; '1' = present, '0' = missing
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_hall_effect_send(mavlink_channel_t chan, float speed, uint8_t left_magnet, uint8_t right_magnet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_HALL_EFFECT_LEN];
	_mav_put_float(buf, 0, speed);
	_mav_put_uint8_t(buf, 4, left_magnet);
	_mav_put_uint8_t(buf, 5, right_magnet);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HALL_EFFECT, buf, MAVLINK_MSG_ID_HALL_EFFECT_LEN, MAVLINK_MSG_ID_HALL_EFFECT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HALL_EFFECT, buf, MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#endif
#else
	mavlink_hall_effect_t packet;
	packet.speed = speed;
	packet.left_magnet = left_magnet;
	packet.right_magnet = right_magnet;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HALL_EFFECT, (const char *)&packet, MAVLINK_MSG_ID_HALL_EFFECT_LEN, MAVLINK_MSG_ID_HALL_EFFECT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HALL_EFFECT, (const char *)&packet, MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_HALL_EFFECT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_hall_effect_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float speed, uint8_t left_magnet, uint8_t right_magnet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, speed);
	_mav_put_uint8_t(buf, 4, left_magnet);
	_mav_put_uint8_t(buf, 5, right_magnet);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HALL_EFFECT, buf, MAVLINK_MSG_ID_HALL_EFFECT_LEN, MAVLINK_MSG_ID_HALL_EFFECT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HALL_EFFECT, buf, MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#endif
#else
	mavlink_hall_effect_t *packet = (mavlink_hall_effect_t *)msgbuf;
	packet->speed = speed;
	packet->left_magnet = left_magnet;
	packet->right_magnet = right_magnet;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HALL_EFFECT, (const char *)packet, MAVLINK_MSG_ID_HALL_EFFECT_LEN, MAVLINK_MSG_ID_HALL_EFFECT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HALL_EFFECT, (const char *)packet, MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE HALL_EFFECT UNPACKING


/**
 * @brief Get field speed from hall_effect message
 *
 * @return Hall Effect sensor averaged speed reading in km/h
 */
static inline float mavlink_msg_hall_effect_get_speed(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field left_magnet from hall_effect message
 *
 * @return flag for presence of left wheel Hall Effect magnet; '1' = present, '0' = missing
 */
static inline uint8_t mavlink_msg_hall_effect_get_left_magnet(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field right_magnet from hall_effect message
 *
 * @return flag for presence of right wheel Hall Effect magnet; '1' = present, '0' = missing
 */
static inline uint8_t mavlink_msg_hall_effect_get_right_magnet(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Decode a hall_effect message into a struct
 *
 * @param msg The message to decode
 * @param hall_effect C-struct to decode the message contents into
 */
static inline void mavlink_msg_hall_effect_decode(const mavlink_message_t* msg, mavlink_hall_effect_t* hall_effect)
{
#if MAVLINK_NEED_BYTE_SWAP
	hall_effect->speed = mavlink_msg_hall_effect_get_speed(msg);
	hall_effect->left_magnet = mavlink_msg_hall_effect_get_left_magnet(msg);
	hall_effect->right_magnet = mavlink_msg_hall_effect_get_right_magnet(msg);
#else
	memcpy(hall_effect, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_HALL_EFFECT_LEN);
#endif
}
