#pragma once

#define Kilobytes(Bytes) (Bytes * 1024LL)
#define Megabytes(Bytes) (Kilobytes(Bytes) * 1024LL)
#define Gigabytes(Bytes) (Megabytes(Bytes) * 1024LL)
#define Terabytes(Bytes) (Gigabytes(Bytes) * 1024LL)

struct memory_arena
{
	umm Size;
	umm Used;
	void *Base;
};

inline void
InitMemoryArena(memory_arena *Arena, void *Memory, umm Size)
{
	Arena->Base = Memory;
	Arena->Size = Size;
	Arena->Used = 0;
}

inline void *
PushSize(memory_arena *Arena, umm Size)
{
	Assert(Arena->Used + Size < Arena->Size);

	void *Result = (u8 *)Arena->Base + Arena->Used;
	Arena->Used += Size;

	return Result;
}

#define PushStruct(Arena, Type) PushSize(Arena, sizeof(Type))
#define PushArray(Arena, Count, Type) PushSize(Arena, Count * sizeof(Type))