using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    public class Pool
    {
        private readonly Allocator<EntityElement> mEntitiesAllocator;

        private readonly ComponentType[] mComponents;
        
        private readonly bool[] mComponentsExisted;
        private readonly uint[] mComponentsMapped;

        private readonly uint mComponentCount;

        public Pool(uint reserve = 255, params ComponentType[] components)
        {
            mEntitiesAllocator = new Allocator<EntityElement>(reserve);
            
            mComponents = components;
            
            mComponentsExisted = new bool[ComponentInfo.Components.Length];
            mComponentsMapped = new uint[ComponentInfo.Components.Length];

            for (uint index = 0; index < mComponents.Length; index++)
            {
                mComponentsExisted[mComponents[index].Identity] = true;
                mComponentsMapped[mComponents[index].Identity] = index;
            }

            mComponentCount = (uint)mComponents.Length;
        }

        public void AddComponent(Entity entity, Component component)
        {
            Utility.Assert(mComponentsExisted[component.Type.Identity], "Error: Pool do not support this component.");

            var mappedIdentity = mComponentsMapped[component.Type.Identity];

            mEntitiesAllocator.Elements[entity.Identity].SetComponent(mappedIdentity, component, 1);
        }

        public void AddComponent<Component>(Entity entity) where Component : LightEntities.Component, new()
        {
            AddComponent(entity, new Component());
        }

        public void RemoveComponent(Entity entity, Component component)
        {
            Utility.Assert(mComponentsExisted[component.Type.Identity], "Error: Pool do not support this component.");

            var mappedIdentity = mComponentsMapped[component.Type.Identity];

            mEntitiesAllocator.Elements[entity.Identity].SetComponent(mappedIdentity, null, 0);
        }

        public void RemoveComponent<Component>(Entity entity) where Component : LightEntities.Component
        {
            var identity = LightEntities.ComponentInfo.TypeOf<Component>().Identity;
            var mappedIdentity = mComponentsMapped[identity];

            Utility.Assert(mComponentsExisted[identity], "Error: Pool do not support this component.");

            mEntitiesAllocator.Elements[entity.Identity].SetComponent(mappedIdentity, null, 0);
        }

        public Component GetComponent<Component>(Entity entity) where Component : LightEntities.Component
        {
            var identity = LightEntities.ComponentInfo.TypeOf<Component>().Identity;

            Utility.Assert(mComponentsExisted[identity], "Error: Pool do not support this component.");

            return mEntitiesAllocator.Elements[entity.Identity].Components[mComponentsMapped[identity]] as Component;
        }

        public Component GetComponent(Entity entity, ComponentType type)
        {
            Utility.Assert(mComponentsExisted[type.Identity], "Error : Pool do not support this component.");

            return mEntitiesAllocator.Elements[entity.Identity].Components[mComponentsMapped[type.Identity]];
        }

        public Entity Allocate()
        {
            return new Entity(this, mEntitiesAllocator.Allocate(new EntityElement(mComponentCount)));
        }

        public void Free(ref Entity entity)
        {
            Utility.Assert(entity != null, "Error: Cannot free null.");

            mEntitiesAllocator.Free(entity.Identity);
            
            entity = null;
        }

        public List<Entity> Match(Match match)
        {
            List<Entity> entities = new List<Entity>();

            BitSet matchRule = new BitSet(mComponentCount);

            foreach (var component in match.Components)
            {
                if (!mComponentsExisted[component.Identity]) return entities;

                matchRule.Set(mComponentsMapped[component.Identity], 1);
            }

            for (uint index = 0; index < mEntitiesAllocator.MaxLocation; index++)
            {
                var element = mEntitiesAllocator.Elements[index];

                if (element == null) continue;

                if (element.Bit.AndEqual(matchRule)) entities.Add(new Entity(this, index));
            }

            return entities;
        }
    }
}
