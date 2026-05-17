module;

#include <cstddef>
#ifdef __unix__
#include <sys/mman.h>
#include <unistd.h>
#endif
#ifdef _WIN32
#include <memoryapi.h>
#include <sysinfoapi.h>
#endif

export module core.memory.pageAllocator;
export import core.memory.allocator;
export import core.memory.slice;

export namespace draco::memory
{
	namespace page
	{
		using namespace std;
#ifdef __unix__
		Error alloc(
			Allocator alloc,
			Slice *dst,
			size_t size,
			size_t align
		)
		{
			int pageSizeSub1 = getpagesize() - 1;
			size_t reqSize = (size + (pageSizeSub1)) & (~pageSizeSub1);
			void *ptr = mmap(
				nullptr,
				reqSize,
				PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_PRIVATE,
				-1,
				0
			);
			if (((ptrdiff_t)ptr) == -1)
			{
				return Error::OutOfMemory;
			}
			dst->data = ptr;
			dst->size = reqSize;
			return Error::Okay;
		}

		Error free(Allocator alloc, Slice block)
		{
			munmap(block.data, block.size);
			return Error::Okay;
		}
#endif
#ifdef _WIN32
		AllocatorError alloc(
			Allocator alloc,
			Slice *dst,
			size_t size,
			size_t align
		)
		{
			SYSTEM_INFO sysinfo;
			unsigned long pageSizeSub1;
			size_t reqSize;
			void *ptr;
			GetSystemInfo(&sysinfo);
			pageSizeSub1 = sysinfo.dwAllocationGranularity - 1;
			reqSize = (size + (pageSizeSub1)) & (~pageSizeSub1);
			ptr = VirtualAlloc(
				nullptr,
				reqSize,
				MEM_COMMIT | MEM_RESERVE,
				PAGE_READWRITE
			);
			if (ptr == nullptr)
			{
				return AllocatorError::OutOfMemory;
			}
			dst->data = ptr;
			dst->size = reqSize;
			return AllocatorError::Okay;
		}

		AllocatorError allocLargePages(
			Allocator alloc,
			Slice *dst,
			size_t size,
			size_t align
		)
		{
			size_t pageSizeSub1 = GetLargePageMinimum() - 1;
			size_t reqSize = (size + (pageSizeSub1)) & (~pageSizeSub1);
			void *ptr;
			ptr = VirtualAlloc(
				nullptr,
				reqSize,
				MEM_COMMIT | MEM_RESERVE | MEM_LARGE_PAGES,
				PAGE_READWRITE
			);
			if (ptr == nullptr)
			{
				return AllocatorError::OutOfMemory;
			}
			dst->data = ptr;
			dst->size = reqSize;
			return AllocatorError::Okay;
		}

		void free(Allocator alloc, Slice block)
		{
			VirtualFree(block.data, block.size, MEM_DECOMMIT | MEM_RELEASE);
		}
#endif

		AllocatorVTbl pageAllocatorVtbl = {
			.alloc = alloc,
			.free = free,
			.freeAll = nilFreeAll,
		};
		Allocator pageAllocator = {
			.vtbl = &pageAllocatorVtbl,
			.allocatorData = nullptr,
		};
	}
}
