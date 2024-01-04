#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>


int main(int argc, char ** argv)
{
	int fd = open(argv[1], O_RDONLY); 
	if(fd < 0) {
		perror("open()");
		return -1;
	}

	off_t len = lseek(fd, 0, SEEK_END);
	void* data_compressed = mmap(NULL, len, PROT_READ, MAP_FILE|MAP_PRIVATE, fd, 0);
	if(data_compressed == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}
	void* data_uncompressed = malloc(10*len);

	fprintf(stderr, "compressing\n");
	
	uint64_t data_uncompressed_len;
	int status = uncompress(data_uncompressed, &data_uncompressed_len, data_compressed, len);
	write(1, data_uncompressed, data_uncompressed_len);
	fprintf(stderr, "compressed\n");
	return 0;
}
