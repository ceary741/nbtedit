#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


#include "nbt.h"

nbt chunkStructed(chunk_data data);
int freeChunk(nbt data);
nbt_tag (*parseNbtTag[NBT_NUM])(nbt_pointer nbtp)
{
	[TAG_END]			parseEnd,
	[TAG_BYTE]          parseByte,
	[TAG_SHORT]         parseShort,
	[TAG_INT]           parseInt,
	[TAG_LONG]          parseLong,
	[TAG_FLOAT]         parseFloat,
	[TAG_DOUBLE]        parseDouble,
	[TAG_BYTEARRAY]     parseByteArray,
	[TAG_STRING]        parseString,
	[TAG_LIST]          parseList,
	[TAG_COMPOUND]      parseCompound,
	[TAG_INTARRAY]      parseIntArray,
	[TAG_LONGARRAY]     parseLongArray,
};

int main(void)
{
	int fd = open("../data/chunk/q.nbt", O_RDONLY); 
	int len = lseek(fd, 0, SEEK_END);
	chunk_data data = mmap(NULL, len, PROT_NONE, MAP_FILE, fd, 0);


	return 0;
}

//nbt chunkStructed(chunk_data data)
//{


