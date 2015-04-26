// MESSAGE EXTRA2 PACKING

#define MAVLINK_MSG_ID_EXTRA2 159

typedef struct __mavlink_extra2_t
{
 uint16_t extra3; ///<  backup variable3
 uint8_t extra1; ///<  backup variable1
 uint8_t extra2; ///<  backup variable2
} mavlink_extra2_t;

#define MAVLINK_MSG_ID_EXTRA2_LEN 4
#define MAVLINK_MSG_ID_159_LEN 4

#define MAVLINK_MSG_ID_EXTRA2_CRC 53
#define MAVLINK_MSG_ID_159_CRC 53



#define MAVLINK_MESSAGE_INFO_EXTRA2 { \
	"EXTRA2", \
	3, \
	{  { "extra3", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_extra2_t, extra3) }, \
         { "extra1", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_extra2_t, extra1) }, \
         { "extra2", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_extra2_t, extra2) }, \
         } \
}


/**
 * @brief Pack a extra2 message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param extra1  backup variable1
 * @param extra2  backup variable2
 * @param extra3  backup variable3
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_extra2_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t extra1, uint8_t extra2, uint16_t extra3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_EXTRA2_LEN];
	_mav_put_uint16_t(buf, 0, extra3);
	_mav_put_uint8_t(buf, 2, extra1);
	_mav_put_uint8_t(buf, 3, extra2);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EXTRA2_LEN);
#else
	mavlink_extra2_t packet;
	packet.extra3 = extra3;
	packet.extra1 = extra1;
	packet.extra2 = extra2;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EXTRA2_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_EXTRA2;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_EXTRA2_LEN, MAVLINK_MSG_ID_EXTRA2_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_EXTRA2_LEN);
#endif
}

/**
 * @brief Pack a extra2 message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param extra1  backup variable1
 * @param extra2  backup variable2
 * @param extra3  backup variable3
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_extra2_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t extra1,uint8_t extra2,uint16_t extra3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_EXTRA2_LEN];
	_mav_put_uint16_t(buf, 0, extra3);
	_mav_put_uint8_t(buf, 2, extra1);
	_mav_put_uint8_t(buf, 3, extra2);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EXTRA2_LEN);
#else
	mavlink_extra2_t packet;
	packet.extra3 = extra3;
	packet.extra1 = extra1;
	packet.extra2 = extra2;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EXTRA2_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_EXTRA2;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_EXTRA2_LEN, MAVLINK_MSG_ID_EXTRA2_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_EXTRA2_LEN);
#endif
}

/**
 * @brief Encode a extra2 struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param extra2 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_extra2_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_extra2_t* extra2)
{
	return mavlink_msg_extra2_pack(system_id, component_id, msg, extra2->extra1, extra2->extra2, extra2->extra3);
}

/**
 * @brief Encode a extra2 struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param extra2 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_extra2_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_extra2_t* extra2)
{
	return mavlink_msg_extra2_pack_chan(system_id, component_id, chan, msg, extra2->extra1, extra2->extra2, extra2->extra3);
}

/**
 * @brief Send a extra2 message
 * @param chan MAVLink channel to send the message
 *
 * @param extra1  backup variable1
 * @param extra2  backup variable2
 * @param extra3  backup variable3
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_extra2_send(mavlink_channel_t chan, uint8_t extra1, uint8_t extra2, uint16_t extra3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_EXTRA2_LEN];
	_mav_put_uint16_t(buf, 0, extra3);
	_mav_put_uint8_t(buf, 2, extra1);
	_mav_put_uint8_t(buf, 3, extra2);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA2, buf, MAVLINK_MSG_ID_EXTRA2_LEN, MAVLINK_MSG_ID_EXTRA2_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA2, buf, MAVLINK_MSG_ID_EXTRA2_LEN);
#endif
#else
	mavlink_extra2_t packet;
	packet.extra3 = extra3;
	packet.extra1 = extra1;
	packet.extra2 = extra2;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA2, (const char *)&packet, MAVLINK_MSG_ID_EXTRA2_LEN, MAVLINK_MSG_ID_EXTRA2_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA2, (const char *)&packet, MAVLINK_MSG_ID_EXTRA2_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_EXTRA2_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_extra2_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t extra1, uint8_t extra2, uint16_t extra3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint16_t(buf, 0, extra3);
	_mav_put_uint8_t(buf, 2, extra1);
	_mav_put_uint8_t(buf, 3, extra2);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA2, buf, MAVLINK_MSG_ID_EXTRA2_LEN, MAVLINK_MSG_ID_EXTRA2_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA2, buf, MAVLINK_MSG_ID_EXTRA2_LEN);
#endif
#else
	mavlink_extra2_t *packet = (mavlink_extra2_t *)msgbuf;
	packet->extra3 = extra3;
	packet->extra1 = extra1;
	packet->extra2 = extra2;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA2, (const char *)packet, MAVLINK_MSG_ID_EXTRA2_LEN, MAVLINK_MSG_ID_EXTRA2_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA2, (const char *)packet, MAVLINK_MSG_ID_EXTRA2_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE EXTRA2 UNPACKING


/**
 * @brief Get field extra1 from extra2 message
 *
 * @return  backup variable1
 */
static inline uint8_t mavlink_msg_extra2_get_extra1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field extra2 from extra2 message
 *
 * @return  backup variable2
 */
static inline uint8_t mavlink_msg_extra2_get_extra2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field extra3 from extra2 message
 *
 * @return  backup variable3
 */
static inline uint16_t mavlink_msg_extra2_get_extra3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a extra2 message into a struct
 *
 * @param msg The message to decode
 * @param extra2 C-struct to decode the message contents into
 */
static inline void mavlink_msg_extra2_decode(const mavlink_message_t* msg, mavlink_extra2_t* extra2)
{
#if MAVLINK_NEED_BYTE_SWAP
	extra2->extra3 = mavlink_msg_extra2_get_extra3(msg);
	extra2->extra1 = mavlink_msg_extra2_get_extra1(msg);
	extra2->extra2 = mavlink_msg_extra2_get_extra2(msg);
#else
	memcpy(extra2, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_EXTRA2_LEN);
#endif
}
