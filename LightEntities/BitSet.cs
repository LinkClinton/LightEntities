using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    public class BitSet
    {
        private uint[] mBits;

        public BitSet(uint length)
        {
            Utility.Assert(length != 0, "Error: Bitset's length can not be 0.");

            mBits = new uint[((length - 1) >> 5) + 1];
        }

        public void Set(uint location, uint value)
        {
            Utility.Assert(value == 0 || value == 1, "Error: value must be 1 or 0.");

            var arrayIndex = location >> 5;
            var bitIndex = location - (arrayIndex << 5);

            var mask = (uint)1 << (int)bitIndex;

            mBits[arrayIndex] = value == 1 ?
                mBits[arrayIndex] | mask :
                mBits[arrayIndex] & (~mask);
        }

        public void And(BitSet bitSet)
        {
            Utility.Assert(mBits.Length == bitSet.mBits.Length, "Error: length must be same.");

            for (uint index = 0; index < mBits.Length; index++)
                mBits[index] = mBits[index] & bitSet.mBits[index];
        }

        public bool AndEqual(BitSet bitSet)
        {
            Utility.Assert(mBits.Length == bitSet.mBits.Length, "Error: length must be same.");

            for (uint index = 0; index < mBits.Length; index++)
                if ((mBits[index] & bitSet.mBits[index]) != bitSet.mBits[index]) return false;

            return true;
        }

        public static BitSet And(BitSet left, BitSet right)
        {
            Utility.Assert(left.mBits.Length == right.mBits.Length, "Error: length must be same.");

            BitSet bitSet = new BitSet((uint)left.mBits.Length * 32);

            for (uint index = 0; index < bitSet.mBits.Length; index++)
                bitSet.mBits[index] = left.mBits[index] & right.mBits[index];

            return bitSet;
        }
    }
}
