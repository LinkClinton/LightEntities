using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    public static class ComponentInfo
    {
        private static readonly Type mRootType = typeof(object);
        private static readonly Type mComponentType = typeof(Component);
        
        private static readonly Dictionary<Type, ComponentType> mTypeMapped;
        private static readonly Dictionary<Type, ComponentType> mBaseTypeMapped;

        public static ComponentType[] Components => mTypeMapped.Values.ToArray();

        private static bool IsInheritFrom(Type type, Type baseType)
        {
            if (baseType == mRootType) return true;

            while (type.BaseType != mRootType)
            {
                type = type.BaseType;

                if (type == baseType) return true;
            }

            return false;
        }

        private static void ApplyType(Type type, Type baseType)
        {
            if (!mBaseTypeMapped.ContainsKey(baseType))
                mBaseTypeMapped.Add(baseType, new ComponentType(baseType, Convert.ToUInt32(mBaseTypeMapped.Count)));

            mTypeMapped.Add(type, mBaseTypeMapped[baseType]);
        }

        static ComponentInfo()
        {
            mTypeMapped = new Dictionary<Type, ComponentType>();
            mBaseTypeMapped = new Dictionary<Type, ComponentType>();
        }

        public static ComponentType TypeOf(Type type)
        {
            Utility.Assert(mTypeMapped.ContainsKey(type), "Error: type is not component type or initialized.");

            return mTypeMapped[type];
        }

        public static ComponentType TypeOf<Component>() where Component : LightEntities.Component
        {
            return TypeOf(typeof(Component));
        }

        public static void InitializeComponents()
        {
            InitializeComponents(global::System.Reflection.Assembly.GetExecutingAssembly());
        }

        public static void InitializeComponents(global::System.Reflection.Assembly assembly)
        {
            var ComponentAttributeType = typeof(Attribute.ComponentAttribute);

            foreach (var type in assembly.DefinedTypes)
            {
                if (!IsInheritFrom(type, mComponentType) && type != mComponentType) continue;

                var attribute = global::System.Attribute.GetCustomAttribute(type, ComponentAttributeType, false);

                if (attribute == null) throw new Exception("Error: Component without ComponentAttribute.");

                ApplyType(type, (attribute as Attribute.ComponentAttribute).ComponentClassType);
            }
        }
    }
}
