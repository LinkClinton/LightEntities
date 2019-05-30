using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    [Attribute.Component(typeof(Component))]
    public class Component
    {
        public ComponentType Type { get; }

        public Component()
        {
            Type = ComponentInfo.TypeOf(GetType());
        }
    }
}
