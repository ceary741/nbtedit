#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <arpa/inet.h>



#include "cnbt.h"
#include "print_nbt.h"
#include "get_chunk.h"

int main(void)
{
	chunk_data data;
	getChunk(&data, 256, 256);
	puts("---------------------");
	nbt this_nbt = chunkStructed(data);
	if(this_nbt == NULL)
	{
		puts("error!");
	} 
	/*
	else {
		printf("data - seek = %lld\n", (uint64_t)data - (uint64_t)seek);
	}
	*/

	printNbt(this_nbt, 0);

	return 0;
}

