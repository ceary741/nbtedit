#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <arpa/inet.h>



#include "nbt.h"
#include "cnbt.h"

nbt_load (*readNbtsLoad[NBT_NUM])(nbt_pointer *pseek) = 
{
//	[TAG_END]			=	readEnd,
	[TAG_BYTE]			=	readByte,
	[TAG_SHORT]			=	readShort,
	[TAG_INT]			=	readInt,
	[TAG_LONG]			=	readLong,
	[TAG_FLOAT]			=	readFloat,
	[TAG_DOUBLE]		=	readDouble,
	[TAG_BYTEARRAY]		=	readByteArray,
	[TAG_STRING]		=	readString,
	[TAG_LIST]			=	readList,
	[TAG_COMPOUND]		=	readCompound,
	[TAG_INTARRAY]		=	readIntArray,
	[TAG_LONGARRAY]		=	readLongArray,
};

/*
int main(void)
{
	int fd = open("../data/chunk/q.nbt", O_RDONLY); 
	int len = lseek(fd, 0, SEEK_END);
	chunk_data data = mmap(NULL, len, PROT_READ, MAP_FILE|MAP_PRIVATE, fd, 0);
	if(data == MAP_FAILED)
	{
		perror("mmap()");
		return -1;
	}
	
	if( *((uint8_t*)data) != TAG_COMPOUND)
	{
		return -1;
	}
	data++;

	if( *((uint16_t*)data) != 0x00)
	{
		return -1;
	}
	data += 2;

	nbt_pointer seek = chunkStructed(data);
	if(seek == NULL)
	{
		puts("error!");
	} else {
		printf("data - seek = %lld\n", (uint64_t)data - (uint64_t)seek);
	}


	return 0;
}
*/

nbt chunkStructed(chunk_data data)
{
	nbt this_nbt = malloc(sizeof(struct nbt_tag));
	this_nbt -> next = NULL;
	this_nbt -> tag_id = TAG_COMPOUND;
	this_nbt -> name_length = 0;
	this_nbt -> name = NULL;

	//puts("Start");
	if( *((uint8_t*)data) != TAG_COMPOUND)
	{
		return NULL;
	}
	data++;

	if( *((uint16_t*)data) != 0x00)
	{
		return NULL;
	}
	data += 2;

	nbt_pointer *pseek = &data;

	this_nbt -> data = readCompound(pseek);
	//printf("CNT = %d", i);

	//puts("End");
	return this_nbt;
}

nbt_tag nextTag(nbt_tag *plast_next, nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;

	if( *((uint8_t*)seek) == TAG_END)
	{
		*plast_next = NULL;
		*pseek = seek+1;
		return NULL;
	}


	nbt_tag this_tag = malloc(sizeof(struct nbt_tag));
	*plast_next = this_tag;
	this_tag -> next = NULL;
	this_tag -> tag_id = *(uint8_t*)seek;
	seek++;
	this_tag -> name_length = ntohs(*(uint16_t*)seek);
	seek += 2;
	this_tag -> name = malloc(this_tag->name_length + 1);
	memmove(this_tag->name, seek, this_tag->name_length);
	this_tag->name[this_tag->name_length] = '\0';
	seek += this_tag->name_length;
	//puts(this_tag->name);
	*pseek = seek;

	this_tag -> data = readNbtLoad(this_tag, pseek);
	
	return this_tag;
}


nbt_load readNbtLoad(nbt_tag this_tag, nbt_pointer *pseek)
{
	return readNbtsLoad[this_tag->tag_id](pseek);
}

//un
nbt_load readByte(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	nbt_load this_load = malloc(1);
	memmove(this_load, seek, 1);
	seek++;
	*pseek = seek;

	return this_load;
}


//un
nbt_load readShort(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	nbt_load this_load = malloc(2);
	memmove(this_load, seek, 2);
	seek += 2;
	*pseek = seek;

	return this_load;
}
nbt_load readInt(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	nbt_load this_load = malloc(4);
	memmove(this_load, seek, 4);
	seek += 4;
	*pseek = seek;

//	printf("%d\n", ntohl(*(int32_t *)this_load));

	return this_load;
}

nbt_load readLong(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	nbt_load this_load = malloc(8);
	memmove(this_load, seek, 8);
	seek += 8;
	*pseek = seek;

	return this_load;
}

//un
nbt_load readFloat(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	nbt_load this_load = malloc(4);
	memmove(this_load, seek, 4);
	seek += 4;
	*pseek = seek;

	return this_load;
}

//un
nbt_load readDouble(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	nbt_load this_load = malloc(8);
	memmove(this_load, seek, 8);
	seek += 8;
	*pseek = seek;

	return this_load;
}

//un
nbt_load readByteArray(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	uint32_t size = ntohl(*(uint32_t*)seek);
	nbt_load this_load = malloc(size+4);
	memmove(this_load, seek, size+4);
	seek += 4;
	seek += size;

	*pseek = seek;

	return this_load;
}

nbt_load readString(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	uint16_t length = ntohs(*(uint16_t*)seek);
	nbt_load this_load = malloc(length + 2);
	memmove(this_load, seek, length+2);

	/*
	putchar(*(char *)(seek+2));
	putchar(*(char *)(seek+3));
	putchar(*(char *)(seek+4));
	putchar(*(char *)(seek+5));
	*/

	seek += (length + 2);
	*pseek = seek;
	return this_load;
}

nbt_load readList(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	uint8_t tag_id = *(uint8_t*)seek;
	seek++;
	uint32_t size = ntohl(*(uint32_t*)seek);
	printf("num %d\n", size);
	seek += 4;
	nbt_load this_load = malloc(5+8*size);
	*(uint8_t*)this_load = tag_id;
	this_load++;
	*(uint32_t*)this_load = size;
	this_load += 4;
	*pseek = seek;

	for(int i = 0; i < size; i++)
	{
		*(uint64_t *)(this_load + 8*i) = (uint64_t)readNbtsLoad[tag_id](pseek);
	}

	return this_load - 5;
}
nbt_load readCompound(nbt_pointer *pseek)
{
	/*
	nbt_pointer data = *pseek;
	nbt_pointer seek = chunkStructed(data);
	*pseek = seek;
	*/
	//printf("readCompound(): data - seek = %lld\n", (uint64_t)data - (uint64_t)seek);
	nbt this_nbt;
	nbt_tag *pnext;

	pnext = &this_nbt;

	//puts("Start");
	
	int i;
	for(i = 0; i < 999; i++)
	{
		nbt_tag this_tag = nextTag(pnext, pseek);
		if(this_tag == NULL)
		{
			break;
		}
		pnext = &(this_tag -> next);
	}
	//printf("CNT = %d", i);

	//puts("End");
	
	return this_nbt;
}
//un
nbt_load readIntArray(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	uint32_t size = ntohl(*(uint32_t*)seek);
	nbt_load this_load = malloc(4*size+4);
	memmove(this_load, seek, 4*size+4);
	seek += 4;
	seek += 4*size;

	*pseek = seek;

	return this_load;
}
nbt_load readLongArray(nbt_pointer *pseek)
{
	nbt_pointer seek = *pseek;
	uint32_t size = ntohl(*(uint32_t*)seek);
	nbt_load this_load = malloc(8*size+4);
	memmove(this_load, seek, 8*size+4);
	seek += 4;
	seek += 8*size;

	*pseek = seek;

	return this_load;
}
//nbt chunkStructed(chunk_data data)
//{


int nbt_GetArraySize(const nbt array)
{
	if(array -> tag_id != TAG_INTARRAY &&
	   array -> tag_id != TAG_LONGARRAY &&
	   array -> tag_id != TAG_BYTEARRAY)
	{
		return -1;
	}
	return ntohl(*(uint32_t*)(array->data));
}

int nbt_GetArrayItem(const nbt array, int index, uint64_t *value)
{
	if(array -> tag_id != TAG_INTARRAY &&
	   array -> tag_id != TAG_LONGARRAY &&
	   array -> tag_id != TAG_BYTEARRAY)
	{
		return -1;
	}
	*value =  ntohl(*(((uint32_t*)(array->data)) + index + 1));
	return 1;
}

nbt nbt_GetItemOfName(const nbt this_nbt, const char* name)
{
	if(this_nbt -> tag_id != TAG_COMPOUND)
	{
		return NULL;
	}
	nbt_tag next = this_nbt -> data;

	while(next != NULL)
	{
		if(strcmp(name, next -> name) == 0)
		{
			return next;
		}
		next = next -> next;
	}
	return NULL;
}

nbt nbt_GetItemOfIndex(const nbt this_nbt, int index)
{
	if(this_nbt -> tag_id != TAG_COMPOUND)
	{
		return NULL;
	}
	nbt_tag next = this_nbt -> data;

	for(int i = 0; i < index && next != NULL; i++)
	{
		next = next -> next;
	}
	return next;;
}


