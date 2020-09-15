/* LCM type definition class file
 * This file was automatically generated by lcm-gen
 * DO NOT MODIFY BY HAND!!!!
 */

package librav_lcm_msgs;
 
import java.io.*;
import java.util.*;
import lcm.lcm.*;
 
public final class CarRawMag_t implements lcm.lcm.LCMEncodable
{
    public long mtime;
    public float magn[];
 
    public CarRawMag_t()
    {
        magn = new float[3];
    }
 
    public static final long LCM_FINGERPRINT;
    public static final long LCM_FINGERPRINT_BASE = 0xc2ebe073b6fa00c8L;
 
    static {
        LCM_FINGERPRINT = _hashRecursive(new ArrayList<Class<?>>());
    }
 
    public static long _hashRecursive(ArrayList<Class<?>> classes)
    {
        if (classes.contains(librav_lcm_msgs.CarRawMag_t.class))
            return 0L;
 
        classes.add(librav_lcm_msgs.CarRawMag_t.class);
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
        outs.writeLong(this.mtime); 
 
        for (int a = 0; a < 3; a++) {
            outs.writeFloat(this.magn[a]); 
        }
 
    }
 
    public CarRawMag_t(byte[] data) throws IOException
    {
        this(new LCMDataInputStream(data));
    }
 
    public CarRawMag_t(DataInput ins) throws IOException
    {
        if (ins.readLong() != LCM_FINGERPRINT)
            throw new IOException("LCM Decode error: bad fingerprint");
 
        _decodeRecursive(ins);
    }
 
    public static librav_lcm_msgs.CarRawMag_t _decodeRecursiveFactory(DataInput ins) throws IOException
    {
        librav_lcm_msgs.CarRawMag_t o = new librav_lcm_msgs.CarRawMag_t();
        o._decodeRecursive(ins);
        return o;
    }
 
    public void _decodeRecursive(DataInput ins) throws IOException
    {
        this.mtime = ins.readLong();
 
        this.magn = new float[(int) 3];
        for (int a = 0; a < 3; a++) {
            this.magn[a] = ins.readFloat();
        }
 
    }
 
    public librav_lcm_msgs.CarRawMag_t copy()
    {
        librav_lcm_msgs.CarRawMag_t outobj = new librav_lcm_msgs.CarRawMag_t();
        outobj.mtime = this.mtime;
 
        outobj.magn = new float[(int) 3];
        System.arraycopy(this.magn, 0, outobj.magn, 0, 3); 
        return outobj;
    }
 
}

