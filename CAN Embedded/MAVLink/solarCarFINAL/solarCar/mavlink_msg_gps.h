// MESSAGE GPS PACKING

#define MAVLINK_MSG_ID_GPS 156

typedef struct __mavlink_gps_t
{
 char latitude[12]; ///< Direct conversion on mCU to chars for co-ordinates - latitude
 char longitude[12]; ///< Direct conversion on mCU to chars for co-ordinates - longitude
 char time[12]; ///< Direct conversion on mCU to chars for co-ordinates - time
 char date[12]; ///< Direct conversion on mCU to chars for co-ordinates - time
 char lock_error[12]; ///< Error message 'INVALID' broadcast if the GPS has not locked yet.
} mavlink_gps_t;

#define MAVLINK_MSG_ID_GPS_LEN 60
#define MAVLINK_MSG_ID_156_LEN 60

#define MAVLINK_MSG_ID_GPS_CRC 10
#define MAVLINK_MSG_ID_156_CRC 10

#define MAVLINK_MSG_GPS_FIELD_LATITUDE_LEN 12
#define MAVLINK_MSG_GPS_FIELD_LONGITUDE_LEN 12
#define MAVLINK_MSG_GPS_FIELD_TIME_LEN 12
#define MAVLINK_MSG_GPS_FIELD_DATE_LEN 12
#define MAVLINK_MSG_GPS_FIELD_LOCK_ERROR_LEN 12

#define MAVLINK_MESSAGE_INFO_GPS { \
	"GPS", \
	5, \
	{  { "latitude", NULL, MAVLINK_TYPE_CHAR, 12, 0, offsetof(mavlink_gps_t, latitude) }, \
         { "longitude", NULL, MAVLINK_TYPE_CHAR, 12, 12, offsetof(mavlink_gps_t, longitude) }, \
         { "time", NULL, MAVLINK_TYPE_CHAR, 12, 24, offsetof(mavlink_gps_t, time) }, \
         { "date", NULL, MAVLINK_TYPE_CHAR, 12, 36, offsetof(mavlink_gps_t, date) }, \
         { "lock_error", NULL, MAVLINK_TYPE_CHAR, 12, 48, offsetof(mavlink_gps_t, lock_error) }, \
         } \
}


/**
 * @brief Pack a gps message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param latitude Direct conversion on mCU to chars for co-ordinates - latitude
 * @param longitude Direct conversion on mCU to chars for co-ordinates - longitude
 * @param time Direct conversion on mCU to chars for co-ordinates - time
 * @param date Direct conversion on mCU to chars for co-ordinates - time
 * @param lock_error Error message 'INVALID' broadcast if the GPS has not locked yet.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       const char *latitude, const char *longitude, const char *time, const char *date, const char *lock_error)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GPS_LEN];

	_mav_put_char_array(buf, 0, latitude, 12);
	_mav_put_char_array(buf, 12, longitude, 12);
	_mav_put_char_array(buf, 24, time, 12);
	_mav_put_char_array(buf, 36, date, 12);
	_mav_put_char_array(buf, 48, lock_error, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GPS_LEN);
#else
	mavlink_gps_t packet;

	mav_array_memcpy(packet.latitude, latitude, sizeof(char)*12);
	mav_array_memcpy(packet.longitude, longitude, sizeof(char)*12);
	mav_array_memcpy(packet.time, time, sizeof(char)*12);
	mav_array_memcpy(packet.date, date, sizeof(char)*12);
	mav_array_memcpy(packet.lock_error, lock_error, sizeof(char)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GPS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GPS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GPS_LEN);
#endif
}

/**
 * @brief Pack a gps message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param latitude Direct conversion on mCU to chars for co-ordinates - latitude
 * @param longitude Direct conversion on mCU to chars for co-ordinates - longitude
 * @param time Direct conversion on mCU to chars for co-ordinates - time
 * @param date Direct conversion on mCU to chars for co-ordinates - time
 * @param lock_error Error message 'INVALID' broadcast if the GPS has not locked yet.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           const char *latitude,const char *longitude,const char *time,const char *date,const char *lock_error)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GPS_LEN];

	_mav_put_char_array(buf, 0, latitude, 12);
	_mav_put_char_array(buf, 12, longitude, 12);
	_mav_put_char_array(buf, 24, time, 12);
	_mav_put_char_array(buf, 36, date, 12);
	_mav_put_char_array(buf, 48, lock_error, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GPS_LEN);
#else
	mavlink_gps_t packet;

	mav_array_memcpy(packet.latitude, latitude, sizeof(char)*12);
	mav_array_memcpy(packet.longitude, longitude, sizeof(char)*12);
	mav_array_memcpy(packet.time, time, sizeof(char)*12);
	mav_array_memcpy(packet.date, date, sizeof(char)*12);
	mav_array_memcpy(packet.lock_error, lock_error, sizeof(char)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GPS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GPS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GPS_LEN);
#endif
}

/**
 * @brief Encode a gps struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gps_t* gps)
{
	return mavlink_msg_gps_pack(system_id, component_id, msg, gps->latitude, gps->longitude, gps->time, gps->date, gps->lock_error);
}

/**
 * @brief Encode a gps struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gps_t* gps)
{
	return mavlink_msg_gps_pack_chan(system_id, component_id, chan, msg, gps->latitude, gps->longitude, gps->time, gps->date, gps->lock_error);
}

/**
 * @brief Send a gps message
 * @param chan MAVLink channel to send the message
 *
 * @param latitude Direct conversion on mCU to chars for co-ordinates - latitude
 * @param longitude Direct conversion on mCU to chars for co-ordinates - longitude
 * @param time Direct conversion on mCU to chars for co-ordinates - time
 * @param date Direct conversion on mCU to chars for co-ordinates - time
 * @param lock_error Error message 'INVALID' broadcast if the GPS has not locked yet.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gps_send(mavlink_channel_t chan, const char *latitude, const char *longitude, const char *time, const char *date, const char *lock_error)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GPS_LEN];

	_mav_put_char_array(buf, 0, latitude, 12);
	_mav_put_char_array(buf, 12, longitude, 12);
	_mav_put_char_array(buf, 24, time, 12);
	_mav_put_char_array(buf, 36, date, 12);
	_mav_put_char_array(buf, 48, lock_error, 12);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, buf, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, buf, MAVLINK_MSG_ID_GPS_LEN);
#endif
#else
	mavlink_gps_t packet;

	mav_array_memcpy(packet.latitude, latitude, sizeof(char)*12);
	mav_array_memcpy(packet.longitude, longitude, sizeof(char)*12);
	mav_array_memcpy(packet.time, time, sizeof(char)*12);
	mav_array_memcpy(packet.date, date, sizeof(char)*12);
	mav_array_memcpy(packet.lock_error, lock_error, sizeof(char)*12);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, (const char *)&packet, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, (const char *)&packet, MAVLINK_MSG_ID_GPS_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_GPS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gps_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const char *latitude, const char *longitude, const char *time, const char *date, const char *lock_error)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;

	_mav_put_char_array(buf, 0, latitude, 12);
	_mav_put_char_array(buf, 12, longitude, 12);
	_mav_put_char_array(buf, 24, time, 12);
	_mav_put_char_array(buf, 36, date, 12);
	_mav_put_char_array(buf, 48, lock_error, 12);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, buf, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, buf, MAVLINK_MSG_ID_GPS_LEN);
#endif
#else
	mavlink_gps_t *packet = (mavlink_gps_t *)msgbuf;

	mav_array_memcpy(packet->latitude, latitude, sizeof(char)*12);
	mav_array_memcpy(packet->longitude, longitude, sizeof(char)*12);
	mav_array_memcpy(packet->time, time, sizeof(char)*12);
	mav_array_memcpy(packet->date, date, sizeof(char)*12);
	mav_array_memcpy(packet->lock_error, lock_error, sizeof(char)*12);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, (const char *)packet, MAVLINK_MSG_ID_GPS_LEN, MAVLINK_MSG_ID_GPS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS, (const char *)packet, MAVLINK_MSG_ID_GPS_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE GPS UNPACKING


/**
 * @brief Get field latitude from gps message
 *
 * @return Direct conversion on mCU to chars for co-ordinates - latitude
 */
static inline uint16_t mavlink_msg_gps_get_latitude(const mavlink_message_t* msg, char *latitude)
{
	return _MAV_RETURN_char_array(msg, latitude, 12,  0);
}

/**
 * @brief Get field longitude from gps message
 *
 * @return Direct conversion on mCU to chars for co-ordinates - longitude
 */
static inline uint16_t mavlink_msg_gps_get_longitude(const mavlink_message_t* msg, char *longitude)
{
	return _MAV_RETURN_char_array(msg, longitude, 12,  12);
}

/**
 * @brief Get field time from gps message
 *
 * @return Direct conversion on mCU to chars for co-ordinates - time
 */
static inline uint16_t mavlink_msg_gps_get_time(const mavlink_message_t* msg, char *time)
{
	return _MAV_RETURN_char_array(msg, time, 12,  24);
}

/**
 * @brief Get field date from gps message
 *
 * @return Direct conversion on mCU to chars for co-ordinates - time
 */
static inline uint16_t mavlink_msg_gps_get_date(const mavlink_message_t* msg, char *date)
{
	return _MAV_RETURN_char_array(msg, date, 12,  36);
}

/**
 * @brief Get field lock_error from gps message
 *
 * @return Error message 'INVALID' broadcast if the GPS has not locked yet.
 */
static inline uint16_t mavlink_msg_gps_get_lock_error(const mavlink_message_t* msg, char *lock_error)
{
	return _MAV_RETURN_char_array(msg, lock_error, 12,  48);
}

/**
 * @brief Decode a gps message into a struct
 *
 * @param msg The message to decode
 * @param gps C-struct to decode the message contents into
 */
static inline void mavlink_msg_gps_decode(const mavlink_message_t* msg, mavlink_gps_t* gps)
{
#if MAVLINK_NEED_BYTE_SWAP
	mavlink_msg_gps_get_latitude(msg, gps->latitude);
	mavlink_msg_gps_get_longitude(msg, gps->longitude);
	mavlink_msg_gps_get_time(msg, gps->time);
	mavlink_msg_gps_get_date(msg, gps->date);
	mavlink_msg_gps_get_lock_error(msg, gps->lock_error);
#else
	memcpy(gps, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_GPS_LEN);
#endif
}
