// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by lcm-gen

#include <string.h>
#include "lcmtypes/librav_lcm_msgs_UAVTrajectory_t.h"

static int __librav_lcm_msgs_UAVTrajectory_t_hash_computed;
static uint64_t __librav_lcm_msgs_UAVTrajectory_t_hash;

uint64_t __librav_lcm_msgs_UAVTrajectory_t_hash_recursive(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __librav_lcm_msgs_UAVTrajectory_t_get_hash)
            return 0;

    __lcm_hash_ptr cp;
    cp.parent =  p;
    cp.v = __librav_lcm_msgs_UAVTrajectory_t_get_hash;
    (void) cp;

    uint64_t hash = (uint64_t)0xf3438377578526b8LL
         + __int64_t_hash_recursive(&cp)
         + __librav_lcm_msgs_UAVTrajectoryPoint_t_hash_recursive(&cp)
        ;

    return (hash<<1) + ((hash>>63)&1);
}

int64_t __librav_lcm_msgs_UAVTrajectory_t_get_hash(void)
{
    if (!__librav_lcm_msgs_UAVTrajectory_t_hash_computed) {
        __librav_lcm_msgs_UAVTrajectory_t_hash = (int64_t)__librav_lcm_msgs_UAVTrajectory_t_hash_recursive(NULL);
        __librav_lcm_msgs_UAVTrajectory_t_hash_computed = 1;
    }

    return __librav_lcm_msgs_UAVTrajectory_t_hash;
}

int __librav_lcm_msgs_UAVTrajectory_t_encode_array(void *buf, int offset, int maxlen, const librav_lcm_msgs_UAVTrajectory_t *p, int elements)
{
    int pos = 0, element;
    int thislen;

    for (element = 0; element < elements; element++) {

        thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].waypoint_num), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __librav_lcm_msgs_UAVTrajectoryPoint_t_encode_array(buf, offset + pos, maxlen - pos, p[element].trajectory, p[element].waypoint_num);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int librav_lcm_msgs_UAVTrajectory_t_encode(void *buf, int offset, int maxlen, const librav_lcm_msgs_UAVTrajectory_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __librav_lcm_msgs_UAVTrajectory_t_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    thislen = __librav_lcm_msgs_UAVTrajectory_t_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int __librav_lcm_msgs_UAVTrajectory_t_encoded_array_size(const librav_lcm_msgs_UAVTrajectory_t *p, int elements)
{
    int size = 0, element;
    for (element = 0; element < elements; element++) {

        size += __int64_t_encoded_array_size(&(p[element].waypoint_num), 1);

        size += __librav_lcm_msgs_UAVTrajectoryPoint_t_encoded_array_size(p[element].trajectory, p[element].waypoint_num);

    }
    return size;
}

int librav_lcm_msgs_UAVTrajectory_t_encoded_size(const librav_lcm_msgs_UAVTrajectory_t *p)
{
    return 8 + __librav_lcm_msgs_UAVTrajectory_t_encoded_array_size(p, 1);
}

int __librav_lcm_msgs_UAVTrajectory_t_decode_array(const void *buf, int offset, int maxlen, librav_lcm_msgs_UAVTrajectory_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].waypoint_num), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        p[element].trajectory = (librav_lcm_msgs_UAVTrajectoryPoint_t*) lcm_malloc(sizeof(librav_lcm_msgs_UAVTrajectoryPoint_t) * p[element].waypoint_num);
        thislen = __librav_lcm_msgs_UAVTrajectoryPoint_t_decode_array(buf, offset + pos, maxlen - pos, p[element].trajectory, p[element].waypoint_num);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int __librav_lcm_msgs_UAVTrajectory_t_decode_array_cleanup(librav_lcm_msgs_UAVTrajectory_t *p, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int64_t_decode_array_cleanup(&(p[element].waypoint_num), 1);

        __librav_lcm_msgs_UAVTrajectoryPoint_t_decode_array_cleanup(p[element].trajectory, p[element].waypoint_num);
        if (p[element].trajectory) free(p[element].trajectory);

    }
    return 0;
}

int librav_lcm_msgs_UAVTrajectory_t_decode(const void *buf, int offset, int maxlen, librav_lcm_msgs_UAVTrajectory_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __librav_lcm_msgs_UAVTrajectory_t_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __librav_lcm_msgs_UAVTrajectory_t_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int librav_lcm_msgs_UAVTrajectory_t_decode_cleanup(librav_lcm_msgs_UAVTrajectory_t *p)
{
    return __librav_lcm_msgs_UAVTrajectory_t_decode_array_cleanup(p, 1);
}

int __librav_lcm_msgs_UAVTrajectory_t_clone_array(const librav_lcm_msgs_UAVTrajectory_t *p, librav_lcm_msgs_UAVTrajectory_t *q, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int64_t_clone_array(&(p[element].waypoint_num), &(q[element].waypoint_num), 1);

        q[element].trajectory = (librav_lcm_msgs_UAVTrajectoryPoint_t*) lcm_malloc(sizeof(librav_lcm_msgs_UAVTrajectoryPoint_t) * q[element].waypoint_num);
        __librav_lcm_msgs_UAVTrajectoryPoint_t_clone_array(p[element].trajectory, q[element].trajectory, p[element].waypoint_num);

    }
    return 0;
}

librav_lcm_msgs_UAVTrajectory_t *librav_lcm_msgs_UAVTrajectory_t_copy(const librav_lcm_msgs_UAVTrajectory_t *p)
{
    librav_lcm_msgs_UAVTrajectory_t *q = (librav_lcm_msgs_UAVTrajectory_t*) malloc(sizeof(librav_lcm_msgs_UAVTrajectory_t));
    __librav_lcm_msgs_UAVTrajectory_t_clone_array(p, q, 1);
    return q;
}

void librav_lcm_msgs_UAVTrajectory_t_destroy(librav_lcm_msgs_UAVTrajectory_t *p)
{
    __librav_lcm_msgs_UAVTrajectory_t_decode_array_cleanup(p, 1);
    free(p);
}

int librav_lcm_msgs_UAVTrajectory_t_publish(lcm_t *lc, const char *channel, const librav_lcm_msgs_UAVTrajectory_t *p)
{
      int max_data_size = librav_lcm_msgs_UAVTrajectory_t_encoded_size (p);
      uint8_t *buf = (uint8_t*) malloc (max_data_size);
      if (!buf) return -1;
      int data_size = librav_lcm_msgs_UAVTrajectory_t_encode (buf, 0, max_data_size, p);
      if (data_size < 0) {
          free (buf);
          return data_size;
      }
      int status = lcm_publish (lc, channel, buf, data_size);
      free (buf);
      return status;
}

struct _librav_lcm_msgs_UAVTrajectory_t_subscription_t {
    librav_lcm_msgs_UAVTrajectory_t_handler_t user_handler;
    void *userdata;
    lcm_subscription_t *lc_h;
};
static
void librav_lcm_msgs_UAVTrajectory_t_handler_stub (const lcm_recv_buf_t *rbuf,
                            const char *channel, void *userdata)
{
    int status;
    librav_lcm_msgs_UAVTrajectory_t p;
    memset(&p, 0, sizeof(librav_lcm_msgs_UAVTrajectory_t));
    status = librav_lcm_msgs_UAVTrajectory_t_decode (rbuf->data, 0, rbuf->data_size, &p);
    if (status < 0) {
        fprintf (stderr, "error %d decoding librav_lcm_msgs_UAVTrajectory_t!!!\n", status);
        return;
    }

    librav_lcm_msgs_UAVTrajectory_t_subscription_t *h = (librav_lcm_msgs_UAVTrajectory_t_subscription_t*) userdata;
    h->user_handler (rbuf, channel, &p, h->userdata);

    librav_lcm_msgs_UAVTrajectory_t_decode_cleanup (&p);
}

librav_lcm_msgs_UAVTrajectory_t_subscription_t* librav_lcm_msgs_UAVTrajectory_t_subscribe (lcm_t *lcm,
                    const char *channel,
                    librav_lcm_msgs_UAVTrajectory_t_handler_t f, void *userdata)
{
    librav_lcm_msgs_UAVTrajectory_t_subscription_t *n = (librav_lcm_msgs_UAVTrajectory_t_subscription_t*)
                       malloc(sizeof(librav_lcm_msgs_UAVTrajectory_t_subscription_t));
    n->user_handler = f;
    n->userdata = userdata;
    n->lc_h = lcm_subscribe (lcm, channel,
                                 librav_lcm_msgs_UAVTrajectory_t_handler_stub, n);
    if (n->lc_h == NULL) {
        fprintf (stderr,"couldn't reg librav_lcm_msgs_UAVTrajectory_t LCM handler!\n");
        free (n);
        return NULL;
    }
    return n;
}

int librav_lcm_msgs_UAVTrajectory_t_subscription_set_queue_capacity (librav_lcm_msgs_UAVTrajectory_t_subscription_t* subs,
                              int num_messages)
{
    return lcm_subscription_set_queue_capacity (subs->lc_h, num_messages);
}

int librav_lcm_msgs_UAVTrajectory_t_unsubscribe(lcm_t *lcm, librav_lcm_msgs_UAVTrajectory_t_subscription_t* hid)
{
    int status = lcm_unsubscribe (lcm, hid->lc_h);
    if (0 != status) {
        fprintf(stderr,
           "couldn't unsubscribe librav_lcm_msgs_UAVTrajectory_t_handler %p!\n", hid);
        return -1;
    }
    free (hid);
    return 0;
}

