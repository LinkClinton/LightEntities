using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    public static class Utility
    {
        [global::System.Diagnostics.Conditional("DEBUG")]
        public static void Assert(bool condition, string message)
        {
            if (!condition) throw new Exception(message);
        }
    }
}
