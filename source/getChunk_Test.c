#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <arpa/inet.h>



#include "nbt.h"
#include "chunk_structed.h"
#include "print_chunk.h"
#include "get_chunk.h"

extern int mcafd;

int main(void)
{
	int fd = open("../data/region/r.0.0.mca", O_RDONLY); 
	mcafd = fd;
	//int len = lseek(fd, 0, SEEK_END);
	//chunk_data data = mmap(NULL, len, PROT_READ, MAP_FILE|MAP_PRIVATE, fd, 0);
	//if(data == MAP_FAILED)
	//{
	//	perror("mmap()");
	//	return -1;
	//}
	
	chunk_data data;
	getChunk(&data, 0, 0);
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

