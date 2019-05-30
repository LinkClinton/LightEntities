using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    public class Entity
    {
        public uint Identity { get; }
        public Pool Pool { get; }

        internal Entity(Pool pool, uint identity)
        {
            Identity = identity;
            Pool = pool;
        }

        public void AddComponent(Component component) 
            => Pool.AddComponent(this, component);

        public void AddComponent<Component>() where Component : LightEntities.Component, new()
            => Pool.AddComponent<Component>(this);

        public void RemoveComponent(Component component)
            => Pool.RemoveComponent(this, component);

        public void RemoveComponent<Component>() where Component : LightEntities.Component
            => Pool.RemoveComponent<Component>(this);

        public Component GetComponent<Component>() where Component : LightEntities.Component
            => Pool.GetComponent<Component>(this);

        public Component GetComponent(ComponentType type)
            => Pool.GetComponent(this, type);
    }
    
    class EntityElement
    {
        public Component[] Components { get; }
        public BitSet Bit { get; }

        public EntityElement(uint size)
        {
            Components = new Component[size];
            Bit = new BitSet(size);
        }

        public void SetComponent(uint location, Component component, uint value)
        {
            Components[location] = component;
            Bit.Set(location, value);
        }
    }
}
