module;

#include <cstddef>

export module core.memory.fixedAllocator;
export import core.memory.allocator;
export import core.memory.slice;

export namespace draco::memory
{
	namespace fixed
	{
		struct FixedAllocator
		{
			void *buffer;
			size_t size;
			bool allocated;
		};

		void init(FixedAllocator *alloc, Slice block)
		{
			alloc->buffer = block.data;
			alloc->size = block.size;
			alloc->allocated = false;
		}

		Error alloc(
			Allocator alloc,
			Slice *dst,
			size_t size,
			size_t align
		)
		{
			FixedAllocator *allocData = (FixedAllocator*)alloc.allocatorData;
			if (allocData->allocated)
			{
				return Error::OutOfMemory;
			}
			else
			{
				dst->data = allocData->buffer;
				dst->size = allocData->size;
				allocData->allocated = true;
				return Error::Okay;
			}
		}

		Error freeAll(Allocator alloc)
		{
			FixedAllocator *allocData = (FixedAllocator*)alloc.allocatorData;
			allocData->allocated = false;
			return Error::Okay;
		}

		AllocatorVTbl fixedAllocatorVtbl = {
			.alloc = alloc,
			.free = nilFree,
			.freeAll = freeAll,
		};

		inline void asAllocator(Allocator *dst, FixedAllocator *alloc)
		{
			asAllocatorVoid(dst, (void*)alloc, &fixedAllocatorVtbl);
		}
	}
}
