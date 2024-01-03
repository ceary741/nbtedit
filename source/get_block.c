#include <stdio.h>

#include "nbt.h"
#include "get_chunk.h"

int toYZX(int x, int y, int z) {
	return y << 8 | z << 4 | x;
}

nbt getBlock(int x, int y, int z)
{
	chunk_data data;
	getChunk(&data, 

