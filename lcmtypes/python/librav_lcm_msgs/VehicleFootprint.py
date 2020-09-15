"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import librav_lcm_msgs.Vector2

class VehicleFootprint(object):
    __slots__ = ["points"]

    __typenames__ = ["librav_lcm_msgs.Vector2"]

    __dimensions__ = [[4]]

    def __init__(self):
        self.points = [ librav_lcm_msgs.Vector2() for dim0 in range(4) ]

    def encode(self):
        buf = BytesIO()
        buf.write(VehicleFootprint._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        for i0 in range(4):
            assert self.points[i0]._get_packed_fingerprint() == librav_lcm_msgs.Vector2._get_packed_fingerprint()
            self.points[i0]._encode_one(buf)

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != VehicleFootprint._get_packed_fingerprint():
            raise ValueError("Decode error")
        return VehicleFootprint._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = VehicleFootprint()
        self.points = []
        for i0 in range(4):
            self.points.append(librav_lcm_msgs.Vector2._decode_one(buf))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if VehicleFootprint in parents: return 0
        newparents = parents + [VehicleFootprint]
        tmphash = (0x6992dd1ff10ce212+ librav_lcm_msgs.Vector2._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if VehicleFootprint._packed_fingerprint is None:
            VehicleFootprint._packed_fingerprint = struct.pack(">Q", VehicleFootprint._get_hash_recursive([]))
        return VehicleFootprint._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)
