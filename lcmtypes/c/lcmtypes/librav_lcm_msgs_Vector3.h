// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by lcm-gen

#ifndef _librav_lcm_msgs_Vector3_h
#define _librav_lcm_msgs_Vector3_h

#include <stdint.h>
#include <stdlib.h>
#include <lcm/lcm_coretypes.h>
#include <lcm/lcm.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _librav_lcm_msgs_Vector3 librav_lcm_msgs_Vector3;
struct _librav_lcm_msgs_Vector3
{
    double     x;
    double     y;
    double     z;
};

/**
 * Create a deep copy of a librav_lcm_msgs_Vector3.
 * When no longer needed, destroy it with librav_lcm_msgs_Vector3_destroy()
 */
librav_lcm_msgs_Vector3* librav_lcm_msgs_Vector3_copy(const librav_lcm_msgs_Vector3* to_copy);

/**
 * Destroy an instance of librav_lcm_msgs_Vector3 created by librav_lcm_msgs_Vector3_copy()
 */
void librav_lcm_msgs_Vector3_destroy(librav_lcm_msgs_Vector3* to_destroy);

/**
 * Identifies a single subscription.  This is an opaque data type.
 */
typedef struct _librav_lcm_msgs_Vector3_subscription_t librav_lcm_msgs_Vector3_subscription_t;

/**
 * Prototype for a callback function invoked when a message of type
 * librav_lcm_msgs_Vector3 is received.
 */
typedef void(*librav_lcm_msgs_Vector3_handler_t)(
    const lcm_recv_buf_t *rbuf, const char *channel,
    const librav_lcm_msgs_Vector3 *msg, void *userdata);

/**
 * Publish a message of type librav_lcm_msgs_Vector3 using LCM.
 *
 * @param lcm The LCM instance to publish with.
 * @param channel The channel to publish on.
 * @param msg The message to publish.
 * @return 0 on success, <0 on error.  Success means LCM has transferred
 * responsibility of the message data to the OS.
 */
int librav_lcm_msgs_Vector3_publish(lcm_t *lcm, const char *channel, const librav_lcm_msgs_Vector3 *msg);

/**
 * Subscribe to messages of type librav_lcm_msgs_Vector3 using LCM.
 *
 * @param lcm The LCM instance to subscribe with.
 * @param channel The channel to subscribe to.
 * @param handler The callback function invoked by LCM when a message is
 *     received. This function is invoked by LCM during calls to lcm_handle()
 *     and lcm_handle_timeout().
 * @param userdata An opaque pointer passed to @p handler when it is invoked.
 * @return 0 on success, <0 if an error occured
 */
librav_lcm_msgs_Vector3_subscription_t* librav_lcm_msgs_Vector3_subscribe(
    lcm_t *lcm, const char *channel, librav_lcm_msgs_Vector3_handler_t handler, void *userdata);

/**
 * Removes and destroys a subscription created by librav_lcm_msgs_Vector3_subscribe()
 */
int librav_lcm_msgs_Vector3_unsubscribe(lcm_t *lcm, librav_lcm_msgs_Vector3_subscription_t* hid);

/**
 * Sets the queue capacity for a subscription.
 * Some LCM providers (e.g., the default multicast provider) are implemented
 * using a background receive thread that constantly revceives messages from
 * the network.  As these messages are received, they are buffered on
 * per-subscription queues until dispatched by lcm_handle().  This function
 * how many messages are queued before dropping messages.
 *
 * @param subs the subscription to modify.
 * @param num_messages The maximum number of messages to queue
 *  on the subscription.
 * @return 0 on success, <0 if an error occured
 */
int librav_lcm_msgs_Vector3_subscription_set_queue_capacity(
    librav_lcm_msgs_Vector3_subscription_t* subs, int num_messages);

/**
 * Encode a message of type librav_lcm_msgs_Vector3 into binary form.
 *
 * @param buf The output buffer.
 * @param offset Encoding starts at this byte offset into @p buf.
 * @param maxlen Maximum number of bytes to write.  This should generally
 *               be equal to librav_lcm_msgs_Vector3_encoded_size().
 * @param msg The message to encode.
 * @return The number of bytes encoded, or <0 if an error occured.
 */
int librav_lcm_msgs_Vector3_encode(void *buf, int offset, int maxlen, const librav_lcm_msgs_Vector3 *p);

/**
 * Decode a message of type librav_lcm_msgs_Vector3 from binary form.
 * When decoding messages containing strings or variable-length arrays, this
 * function may allocate memory.  When finished with the decoded message,
 * release allocated resources with librav_lcm_msgs_Vector3_decode_cleanup().
 *
 * @param buf The buffer containing the encoded message
 * @param offset The byte offset into @p buf where the encoded message starts.
 * @param maxlen The maximum number of bytes to read while decoding.
 * @param msg Output parameter where the decoded message is stored
 * @return The number of bytes decoded, or <0 if an error occured.
 */
int librav_lcm_msgs_Vector3_decode(const void *buf, int offset, int maxlen, librav_lcm_msgs_Vector3 *msg);

/**
 * Release resources allocated by librav_lcm_msgs_Vector3_decode()
 * @return 0
 */
int librav_lcm_msgs_Vector3_decode_cleanup(librav_lcm_msgs_Vector3 *p);

/**
 * Check how many bytes are required to encode a message of type librav_lcm_msgs_Vector3
 */
int librav_lcm_msgs_Vector3_encoded_size(const librav_lcm_msgs_Vector3 *p);

// LCM support functions. Users should not call these
int64_t __librav_lcm_msgs_Vector3_get_hash(void);
uint64_t __librav_lcm_msgs_Vector3_hash_recursive(const __lcm_hash_ptr *p);
int __librav_lcm_msgs_Vector3_encode_array(
    void *buf, int offset, int maxlen, const librav_lcm_msgs_Vector3 *p, int elements);
int __librav_lcm_msgs_Vector3_decode_array(
    const void *buf, int offset, int maxlen, librav_lcm_msgs_Vector3 *p, int elements);
int __librav_lcm_msgs_Vector3_decode_array_cleanup(librav_lcm_msgs_Vector3 *p, int elements);
int __librav_lcm_msgs_Vector3_encoded_array_size(const librav_lcm_msgs_Vector3 *p, int elements);
int __librav_lcm_msgs_Vector3_clone_array(const librav_lcm_msgs_Vector3 *p, librav_lcm_msgs_Vector3 *q, int elements);

#ifdef __cplusplus
}
#endif

#endif
