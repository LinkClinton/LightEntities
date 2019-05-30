using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities.Attribute
{
    [AttributeUsage(AttributeTargets.All, AllowMultiple = false, Inherited = false)]
    public class ComponentAttribute : global::System.Attribute
    {
        public Type ComponentClassType { get; }

        public ComponentAttribute(Type type)
        {
            ComponentClassType = type;
        }
    }
}
