"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class Edge_t(object):
    __slots__ = ["id_start", "id_end"]

    __typenames__ = ["int64_t", "int64_t"]

    __dimensions__ = [None, None]

    def __init__(self):
        self.id_start = 0
        self.id_end = 0

    def encode(self):
        buf = BytesIO()
        buf.write(Edge_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">qq", self.id_start, self.id_end))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != Edge_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return Edge_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = Edge_t()
        self.id_start, self.id_end = struct.unpack(">qq", buf.read(16))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if Edge_t in parents: return 0
        tmphash = (0xda1b389bca30b83c) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if Edge_t._packed_fingerprint is None:
            Edge_t._packed_fingerprint = struct.pack(">Q", Edge_t._get_hash_recursive([]))
        return Edge_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

