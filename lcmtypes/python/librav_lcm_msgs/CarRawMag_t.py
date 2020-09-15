"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class CarRawMag_t(object):
    __slots__ = ["mtime", "magn"]

    __typenames__ = ["int64_t", "float"]

    __dimensions__ = [None, [3]]

    def __init__(self):
        self.mtime = 0
        self.magn = [ 0.0 for dim0 in range(3) ]

    def encode(self):
        buf = BytesIO()
        buf.write(CarRawMag_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">q", self.mtime))
        buf.write(struct.pack('>3f', *self.magn[:3]))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != CarRawMag_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return CarRawMag_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = CarRawMag_t()
        self.mtime = struct.unpack(">q", buf.read(8))[0]
        self.magn = struct.unpack('>3f', buf.read(12))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if CarRawMag_t in parents: return 0
        tmphash = (0xc2ebe073b6fa00c8) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if CarRawMag_t._packed_fingerprint is None:
            CarRawMag_t._packed_fingerprint = struct.pack(">Q", CarRawMag_t._get_hash_recursive([]))
        return CarRawMag_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)
