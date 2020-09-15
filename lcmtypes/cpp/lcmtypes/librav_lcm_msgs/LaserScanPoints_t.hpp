/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#ifndef __librav_lcm_msgs_LaserScanPoints_t_hpp__
#define __librav_lcm_msgs_LaserScanPoints_t_hpp__

#include <lcm/lcm_coretypes.h>

#include <vector>
#include "lcmtypes/librav_lcm_msgs/Pose_t.hpp"
#include "lcmtypes/librav_lcm_msgs/Point3Df_t.hpp"
#include "lcmtypes/librav_lcm_msgs/QuadrotorTransform.hpp"

namespace librav_lcm_msgs
{

class LaserScanPoints_t
{
    public:
        librav_lcm_msgs::Pose_t trans_sensor2world;

        int64_t    point_num;

        std::vector< librav_lcm_msgs::Point3Df_t > points;

        librav_lcm_msgs::QuadrotorTransform pose;

    public:
        /**
         * Encode a message into binary form.
         *
         * @param buf The output buffer.
         * @param offset Encoding starts at thie byte offset into @p buf.
         * @param maxlen Maximum number of bytes to write.  This should generally be
         *  equal to getEncodedSize().
         * @return The number of bytes encoded, or <0 on error.
         */
        inline int encode(void *buf, int offset, int maxlen) const;

        /**
         * Check how many bytes are required to encode this message.
         */
        inline int getEncodedSize() const;

        /**
         * Decode a message from binary form into this instance.
         *
         * @param buf The buffer containing the encoded message.
         * @param offset The byte offset into @p buf where the encoded message starts.
         * @param maxlen The maximum number of bytes to read while decoding.
         * @return The number of bytes decoded, or <0 if an error occured.
         */
        inline int decode(const void *buf, int offset, int maxlen);

        /**
         * Retrieve the 64-bit fingerprint identifying the structure of the message.
         * Note that the fingerprint is the same for all instances of the same
         * message type, and is a fingerprint on the message type definition, not on
         * the message contents.
         */
        inline static int64_t getHash();

        /**
         * Returns "LaserScanPoints_t"
         */
        inline static const char* getTypeName();

        // LCM support functions. Users should not call these
        inline int _encodeNoHash(void *buf, int offset, int maxlen) const;
        inline int _getEncodedSizeNoHash() const;
        inline int _decodeNoHash(const void *buf, int offset, int maxlen);
        inline static uint64_t _computeHash(const __lcm_hash_ptr *p);
};

int LaserScanPoints_t::encode(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;
    int64_t hash = getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int LaserScanPoints_t::decode(const void *buf, int offset, int maxlen)
{
    int pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int LaserScanPoints_t::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t LaserScanPoints_t::getHash()
{
    static int64_t hash = static_cast<int64_t>(_computeHash(NULL));
    return hash;
}

const char* LaserScanPoints_t::getTypeName()
{
    return "LaserScanPoints_t";
}

int LaserScanPoints_t::_encodeNoHash(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;

    tlen = this->trans_sensor2world._encodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &this->point_num, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    for (int a0 = 0; a0 < this->point_num; a0++) {
        tlen = this->points[a0]._encodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = this->pose._encodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int LaserScanPoints_t::_decodeNoHash(const void *buf, int offset, int maxlen)
{
    int pos = 0, tlen;

    tlen = this->trans_sensor2world._decodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this->point_num, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    try {
        this->points.resize(this->point_num);
    } catch (...) {
        return -1;
    }
    for (int a0 = 0; a0 < this->point_num; a0++) {
        tlen = this->points[a0]._decodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = this->pose._decodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int LaserScanPoints_t::_getEncodedSizeNoHash() const
{
    int enc_size = 0;
    enc_size += this->trans_sensor2world._getEncodedSizeNoHash();
    enc_size += __int64_t_encoded_array_size(NULL, 1);
    for (int a0 = 0; a0 < this->point_num; a0++) {
        enc_size += this->points[a0]._getEncodedSizeNoHash();
    }
    enc_size += this->pose._getEncodedSizeNoHash();
    return enc_size;
}

uint64_t LaserScanPoints_t::_computeHash(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for(fp = p; fp != NULL; fp = fp->parent)
        if(fp->v == LaserScanPoints_t::getHash)
            return 0;
    const __lcm_hash_ptr cp = { p, LaserScanPoints_t::getHash };

    uint64_t hash = 0x41cb5b1499974f70LL +
         librav_lcm_msgs::Pose_t::_computeHash(&cp) +
         librav_lcm_msgs::Point3Df_t::_computeHash(&cp) +
         librav_lcm_msgs::QuadrotorTransform::_computeHash(&cp);

    return (hash<<1) + ((hash>>63)&1);
}

}

#endif
