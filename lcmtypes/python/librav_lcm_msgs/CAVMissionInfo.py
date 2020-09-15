"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import librav_lcm_msgs.VehicleState

class CAVMissionInfo(object):
    __slots__ = ["id", "mission_type", "start_state", "goal_state"]

    __typenames__ = ["int64_t", "int32_t", "librav_lcm_msgs.VehicleState", "librav_lcm_msgs.VehicleState"]

    __dimensions__ = [None, None, None, None]

    MT_NEW_MISSION_REQUEST = 1
    MT_ABORT_CURRENT_MISSION = 2

    def __init__(self):
        self.id = 0
        self.mission_type = 0
        self.start_state = librav_lcm_msgs.VehicleState()
        self.goal_state = librav_lcm_msgs.VehicleState()

    def encode(self):
        buf = BytesIO()
        buf.write(CAVMissionInfo._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">qi", self.id, self.mission_type))
        assert self.start_state._get_packed_fingerprint() == librav_lcm_msgs.VehicleState._get_packed_fingerprint()
        self.start_state._encode_one(buf)
        assert self.goal_state._get_packed_fingerprint() == librav_lcm_msgs.VehicleState._get_packed_fingerprint()
        self.goal_state._encode_one(buf)

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != CAVMissionInfo._get_packed_fingerprint():
            raise ValueError("Decode error")
        return CAVMissionInfo._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = CAVMissionInfo()
        self.id, self.mission_type = struct.unpack(">qi", buf.read(12))
        self.start_state = librav_lcm_msgs.VehicleState._decode_one(buf)
        self.goal_state = librav_lcm_msgs.VehicleState._decode_one(buf)
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if CAVMissionInfo in parents: return 0
        newparents = parents + [CAVMissionInfo]
        tmphash = (0xcf592362aa43fd14+ librav_lcm_msgs.VehicleState._get_hash_recursive(newparents)+ librav_lcm_msgs.VehicleState._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if CAVMissionInfo._packed_fingerprint is None:
            CAVMissionInfo._packed_fingerprint = struct.pack(">Q", CAVMissionInfo._get_hash_recursive([]))
        return CAVMissionInfo._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

