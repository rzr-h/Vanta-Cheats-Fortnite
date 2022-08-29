#pragma once

#include "Includes.h"
#include "CheatDriver.h"
#include "KernelDriver.h"

std::string find_object_class(INT32 object_id) {
	uint32_t ChunkOffset = (uint32_t)((int)(object_id) >> 16);
	uint16_t NameOffset = (uint16_t)object_id;

	uint64_t NamePoolChunk = read_virtual<uint64_t>(BaseAddress + 0xcc47500 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
	uint16_t nameEntry = read_virtual<uint16_t>(NamePoolChunk);

	int nameLength = nameEntry >> 6;
	char buff[1024];
	if ((uint32_t)nameLength)
	{
		for (int x = 0; x < nameLength; ++x)
		{
			buff[x] = read_virtual<char>(NamePoolChunk + 4 + x);
		}
		char* v2 = buff;
		unsigned int v4 = nameLength;
		unsigned int v5;
		unsigned int v6;
		__int64 result;
		unsigned int v8;
		int v9;

		v5 = read_virtual<uint64_t>(BaseAddress + 0xcb00868);
		v6 = v5 ^ 0x9C677CC5;
		v8 = v5;
		result = 1041204193 * v5;
		v9 = 0;
		if (v4)
		{
			do
			{
				result = v9 + v8 % 0x21;
				++v9;
				v6 += result;
				*v2++ ^= v6;
			} while (v9 < v4);
		}
		buff[nameLength] = '\0';
		return std::string(buff);
	}
	else
	{
		return "";
	}
}


std::string find_object_name(INT32 object_id) {
	uint32_t ChunkOffset = (uint32_t)((int)(object_id) >> 16);
	uint16_t NameOffset = (uint16_t)object_id;

	uint64_t NamePoolChunk = read_virtual<uint64_t>(BaseAddress + 0xcc47500 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
	if (read_virtual<uint16_t>(NamePoolChunk) < 64)
	{
		auto a1 = read_virtual<DWORD>(NamePoolChunk + 4);
		return find_object_class(a1);
	}
	else
	{
		return find_object_class(object_id);
	}
}