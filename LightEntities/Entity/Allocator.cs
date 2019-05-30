using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightEntities
{
    public class Allocator<Element> where Element : class
    {
        private readonly Queue<uint> mRemainLocations;

        public uint Base { get; }
        public uint Expand { get; }

        public uint MaxLocation { get; private set; }

        public Element[] Elements { get; private set; }

        private static Element[] ExpandElements(Element[] elements, uint expand)
        {
            if (expand == 0) expand = (uint)elements.Length;

            var newElements = new Element[expand << 1];

            elements.CopyTo(newElements, 0);
            
            return newElements;
        }

        public Allocator(uint baseMemory = 255, uint expandMemory = 0)
        {
            Utility.Assert(baseMemory != 0, "Error: Cannot initialize Allocator with 0 size.");

            Base = baseMemory;
            Expand = expandMemory;

            mRemainLocations = new Queue<uint>();

            Elements = new Element[Base];
            MaxLocation = 0;
        }

        public uint Allocate(Element element)
        {
            if (mRemainLocations.Count != 0)
            {
                Elements[mRemainLocations.Peek()] = element;

                return mRemainLocations.Dequeue();
            }

            if (MaxLocation == Elements.Length)
                Elements = ExpandElements(Elements, Expand);

            Elements[MaxLocation] = element;

            return MaxLocation++;
        }

        public void Free(uint identity)
        {
            Elements[identity] = null;

            mRemainLocations.Enqueue(identity);
        }
    }
}
