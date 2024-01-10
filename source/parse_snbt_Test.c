#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "nbt.h"
#include "cnbt.h"
#include "print_nbt.h"
#include "parse_snbt.h"

int main(void)
{
	int fd = open("../data/test.snbt", O_RDONLY); 
	//int fd = open("../data/generator_t2.nbt", O_RDONLY); 
	int len = lseek(fd, 0, SEEK_END);
	char* snbt = mmap(NULL, len, PROT_READ, MAP_FILE|MAP_PRIVATE, fd, 0);
	if(snbt == MAP_FAILED)
	{
		perror("mmap()");
		return -1;
	}

	uint64_t error;
	nbt this_nbt = nbt_ParseSnbt(snbt, len, &error);
	
	/*
	else {
		printf("data - seek = %lld\n", (uint64_t)data - (uint64_t)seek);
	}
	*/

	printNbt(this_nbt, 0);

	//nbt childnbt = nbt_GetItemOfName(this_nbt, "Heightmaps");
	//nbt cchildnbt = nbt_GetItemOfName(childnbt, "OCEAN_FLOOR");
	//int size = nbt_GetArraySize(cchildnbt);
	//printf("%s %d\n", cchildnbt->name, nbt_GetArraySize(cchildnbt));
	//uint64_t value;
	//for(int i = 0; i < size; i++)
	//{
	//	if(nbt_GetArrayItem(cchildnbt, i, &value) < 0)
	//	{
	//		printf("error\n");
	//	}
	//	printf("%lld ", value);
	//}
	//printf("\n");
	//nbt com = nbt_GetItemOfIndex(this_nbt, 8);
	//printf("%p\n%p\n", com, childnbt);

	return 0;
}

