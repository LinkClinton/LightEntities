using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    public class BehaviorSystem
    {
        public Match Match { get; set; }

        public BehaviorSystem()
        {
            Match = new Match();
        }

        public BehaviorSystem(Match match)
        {
            Match = match;
        }

        public BehaviorSystem(params ComponentType[] components)
        {
            Match = new Match(components);
        }

        public virtual void Excute(List<Entity> entities)
        {

        }
    }
}
