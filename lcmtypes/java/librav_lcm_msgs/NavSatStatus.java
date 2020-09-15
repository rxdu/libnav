/* LCM type definition class file
 * This file was automatically generated by lcm-gen
 * DO NOT MODIFY BY HAND!!!!
 */

package librav_lcm_msgs;
 
import java.io.*;
import java.util.*;
import lcm.lcm.*;
 
public final class NavSatStatus implements lcm.lcm.LCMEncodable
{
    public byte status;
    public short service;
 
    public NavSatStatus()
    {
    }
 
    public static final long LCM_FINGERPRINT;
    public static final long LCM_FINGERPRINT_BASE = 0x76b236592075c1dbL;
 
    public static final byte STATUS_NO_FIX = (byte) -1;
    public static final byte STATUS_FIX = (byte) 0;
    public static final byte STATUS_SBAS_FIX = (byte) 1;
    public static final byte STATUS_GBAS_FIX = (byte) 2;
    public static final short SERVICE_GPS = (short) 1;
    public static final short SERVICE_GLONASS = (short) 2;
    public static final short SERVICE_COMPASS = (short) 4;
    public static final short SERVICE_GALILEO = (short) 8;

    static {
        LCM_FINGERPRINT = _hashRecursive(new ArrayList<Class<?>>());
    }
 
    public static long _hashRecursive(ArrayList<Class<?>> classes)
    {
        if (classes.contains(librav_lcm_msgs.NavSatStatus.class))
            return 0L;
 
        classes.add(librav_lcm_msgs.NavSatStatus.class);
        long hash = LCM_FINGERPRINT_BASE
            ;
        classes.remove(classes.size() - 1);
        return (hash<<1) + ((hash>>63)&1);
    }
 
    public void encode(DataOutput outs) throws IOException
    {
        outs.writeLong(LCM_FINGERPRINT);
        _encodeRecursive(outs);
    }
 
    public void _encodeRecursive(DataOutput outs) throws IOException
    {
        outs.writeByte(this.status); 
 
        outs.writeShort(this.service); 
 
    }
 
    public NavSatStatus(byte[] data) throws IOException
    {
        this(new LCMDataInputStream(data));
    }
 
    public NavSatStatus(DataInput ins) throws IOException
    {
        if (ins.readLong() != LCM_FINGERPRINT)
            throw new IOException("LCM Decode error: bad fingerprint");
 
        _decodeRecursive(ins);
    }
 
    public static librav_lcm_msgs.NavSatStatus _decodeRecursiveFactory(DataInput ins) throws IOException
    {
        librav_lcm_msgs.NavSatStatus o = new librav_lcm_msgs.NavSatStatus();
        o._decodeRecursive(ins);
        return o;
    }
 
    public void _decodeRecursive(DataInput ins) throws IOException
    {
        this.status = ins.readByte();
 
        this.service = ins.readShort();
 
    }
 
    public librav_lcm_msgs.NavSatStatus copy()
    {
        librav_lcm_msgs.NavSatStatus outobj = new librav_lcm_msgs.NavSatStatus();
        outobj.status = this.status;
 
        outobj.service = this.service;
 
        return outobj;
    }
 
}

