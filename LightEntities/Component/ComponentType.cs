using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    public class ComponentType
    {
        public Type BaseType { get; }
        public uint Identity { get; }

        public ComponentType(Type type, uint identity)
        {
            BaseType = type;
            Identity = identity;
        }

        public override string ToString()
        {
            return "[BaseType = " + BaseType + ", Identity = " + Identity + "]";
        }
    }
}
