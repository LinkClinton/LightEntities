using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    public class Match
    {
        public ComponentType[] Components { get; }

        public Match(params ComponentType[] components)
        {
            Components = components;
        }
    }
}
