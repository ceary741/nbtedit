#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zlib.h>

#define K *(1024)
#define M *(1024*1024)

#define START 0x0007e005
#define LEN 0x1269

int main(void)
{
	uint64_t data_uncompressed_len;
	void *data_compressed = malloc(8 K);
	void *data_uncompressed = malloc(8 M);

	FILE *mca = fopen("./r.0.0.mca", "r");
	fseek(mca, START, SEEK_SET);
	fread(data_compressed, LEN, 1, mca);
	fclose(mca);

	int status = uncompress(data_uncompressed, &data_uncompressed_len, data_compressed, LEN);
	if (status == Z_OK)
		puts("OK");
	else if (status == Z_DATA_ERROR)
		puts("DATA_ERROR");

	//*((char*)data_uncompressed + data_uncompressed_len) = 0;;
	//puts(data_uncompressed);
	
	FILE *out = fopen("./q.nbt", "w");
	fwrite(data_uncompressed, data_uncompressed_len, 1, out);
//	fwrite(data_compressed, LEN, 1, out);
	fclose(out);

	free(data_compressed);
	free(data_uncompressed);

	return 0;
}

