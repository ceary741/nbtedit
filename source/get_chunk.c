#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <zlib.h>
#include <arpa/inet.h>

#include "get_chunk.h"
#include "cnbt.h"

#define BLOCK_SIZE 4096

int mcafd;

int getChunk(void **chunk, int x, int z)
{
	off_t pos_offset = 4 * ((x & 31) + (z & 31) * 32);
	int fd = getMca(x, z);
	off_t len = lseek(fd, 0, SEEK_END);

	uint32_t chunk_offset_block;
	lseek(fd, pos_offset, SEEK_SET);
	read(fd, &chunk_offset_block, sizeof(chunk_offset_block));
	chunk_offset_block = ntohl(chunk_offset_block);
	int block_num = chunk_offset_block & 0x00ff;
	off_t chunk_offset = (chunk_offset_block >> 8)*BLOCK_SIZE;

	uint32_t data_len;
	lseek(fd, chunk_offset, SEEK_SET);
	read(fd, &data_len, sizeof(data_len));
	data_len = ntohl(data_len);
	data_len -= 1;

	chunk_data data_compressed = mmap(NULL, block_num*BLOCK_SIZE, PROT_READ, MAP_FILE|MAP_PRIVATE, fd, chunk_offset);
	if(data_compressed == MAP_FAILED)
	{
		perror("mmap");
		exit(-1);
	}
	chunk_data data_uncompressed = malloc(10*data_len);

	puts("-----------------------------");
	
	uint64_t data_uncompressed_len;
	int status = uncompress(data_uncompressed, &data_uncompressed_len, data_compressed+5, data_len);
	printf("%ld\n", data_uncompressed_len/data_len);
	*chunk = data_uncompressed;
	return data_uncompressed_len;
}

int getMca(int x, int z)
{
	return mcafd;
}
