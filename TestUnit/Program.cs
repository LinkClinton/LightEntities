using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestUnit
{
    [LightEntities.Attribute.Component(typeof(Component0))]
    class Component0 : LightEntities.Component
    {

    }

    [LightEntities.Attribute.Component(typeof(Component1))]
    class Component1 : LightEntities.Component
    {

    }

    [LightEntities.Attribute.Component(typeof(Component2))]
    class Component2 : LightEntities.Component
    {

    }

    [LightEntities.Attribute.Component(typeof(Component3))]
    class Component3 : LightEntities.Component
    {

    }

    [LightEntities.Attribute.Component(typeof(Component4))]
    class Component4 : LightEntities.Component
    {

    }

    [LightEntities.Attribute.Component(typeof(Component5))]
    class Component5 : LightEntities.Component
    {

    }

    [LightEntities.Attribute.Component(typeof(Component6))]
    class Component6 : LightEntities.Component
    {

    }

    [LightEntities.Attribute.Component(typeof(Component7))]
    class Component7 : LightEntities.Component
    {

    }

    [LightEntities.Attribute.Component(typeof(Component8))]
    class Component8 : LightEntities.Component
    {

    }

    [LightEntities.Attribute.Component(typeof(Component9))]
    class Component9 : LightEntities.Component
    {

    }

    class Program
    {
        static void Main(string[] args)
        {
            LightEntities.ComponentInfo.InitializeComponents();
            LightEntities.ComponentInfo.InitializeComponents(System.Reflection.Assembly.GetExecutingAssembly());

            LightEntities.Entities entities = new LightEntities.Entities();

            uint count = 1000000;

            entities.Pools.Add(new LightEntities.Pool(count,
                LightEntities.ComponentInfo.TypeOf<Component0>(),
                LightEntities.ComponentInfo.TypeOf<Component1>(),
                LightEntities.ComponentInfo.TypeOf<Component2>(),
                LightEntities.ComponentInfo.TypeOf<Component3>(),
                LightEntities.ComponentInfo.TypeOf<Component4>(),
                LightEntities.ComponentInfo.TypeOf<Component5>(),
                LightEntities.ComponentInfo.TypeOf<Component6>(),
                LightEntities.ComponentInfo.TypeOf<Component7>(),
                LightEntities.ComponentInfo.TypeOf<Component8>(),
                LightEntities.ComponentInfo.TypeOf<Component9>()));


            for (uint i = 0; i < count; i++)
            {
                var entity = entities.Pools[0].Allocate();

                entity.AddComponent<Component0>();
                entity.AddComponent<Component1>();
                entity.AddComponent<Component2>();
                entity.AddComponent<Component3>();
                entity.AddComponent<Component4>();
                entity.AddComponent<Component5>();
                entity.AddComponent<Component6>();
                entity.AddComponent<Component7>();
                entity.AddComponent<Component8>();
                entity.AddComponent<Component9>();
            }

            var system0 = new LightEntities.BehaviorSystem(
              LightEntities.ComponentInfo.TypeOf<Component0>(),
              LightEntities.ComponentInfo.TypeOf<Component1>(),
              LightEntities.ComponentInfo.TypeOf<Component2>(),
              LightEntities.ComponentInfo.TypeOf<Component3>(),
              LightEntities.ComponentInfo.TypeOf<Component4>(),
              LightEntities.ComponentInfo.TypeOf<Component5>(),
              LightEntities.ComponentInfo.TypeOf<Component6>(),
              LightEntities.ComponentInfo.TypeOf<Component7>(),
              LightEntities.ComponentInfo.TypeOf<Component8>(),
              LightEntities.ComponentInfo.TypeOf<Component9>());

            var start = DateTime.Now;

            entities.Excute(system0);

            var end = DateTime.Now;

            Console.WriteLine((end - start).TotalSeconds);

            Console.ReadKey();
        }
    }
}
