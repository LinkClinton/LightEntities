using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    public class Entities
    {
        public List<Pool> Pools { get; }

        public Entities()
        {
            Pools = new List<Pool>();
        }

        public void Excute(BehaviorSystem system)
        {
            List<Entity> entities = new List<Entity>();

            foreach (var pool in Pools)
                entities.AddRange(pool.Match(system.Match));

            system.Excute(entities);
        }
    }
}
