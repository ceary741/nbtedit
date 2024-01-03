#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nbt.h"
#include "print_nbt.h"

char *TAG_NAME[NBT_NUM] = 
{
	"End",
	"Byte",
	"Short",
	"Int",
	"Long",
	"Float",
	"Double",
	"ByteArray",
	"String",
	"List",
	"Compound",
	"IntArray",
	"LongArray",
};

int printNbt(nbt this_nbt, int print_load)
{
	return _printNbt(this_nbt, print_load, 0);
}
	
int printdp(int dp)
{
	for(int j = 0; j < dp; j++)
	{
		putchar('\t');
	}

	return 0;

}
int _printNbt(nbt this_nbt, int print_load, int dp)
{
	nbt_tag this_tag = (nbt_tag)(this_nbt);
	for(int i = 0; i < 9999; i++)
	{
		printdp(dp);
		printf("%d %s : %s\n", i, TAG_NAME[this_tag->tag_id], this_tag -> name);
		void *data = this_tag -> data;
		if(this_tag -> tag_id == TAG_COMPOUND)
		{
			if(this_tag -> data == NULL)
			{
				printdp(dp);
				printf("{}\n");
			} else {
				printdp(dp);
				printf("{\n");
				_printNbt(this_tag -> data, print_load, dp+1);
				printdp(dp);
				printf("}\n");
			}
		}
		else if(this_tag -> tag_id == TAG_LIST && *(uint8_t *)data == TAG_COMPOUND)
		{
			data++;
			int num = *(uint32_t*)data;
			data += 4;
			//printf("num %d\n", num);
			if(num == 0)
			{
				printdp(dp);
				printf("[]\n");
			} else {
				printdp(dp);
				printf("[\n");
				for(int j = 0; j < num; j++)
				{
					printdp(dp);
					printf("{\n");
					_printNbt((nbt)*(uint64_t*)(data+j*8), print_load, dp+1);
					printdp(dp);
					printf("}\n");
				}
				printdp(dp);
				printf("]\n");
			}
			
		}
		/*
		else if(this_tag -> tag_id == TAG_LIST)
		{
			data++;
			int num = *(uint32_t*)data;
			data += 4;
			printf("num %d\n", num);
			if(num == 0)
			{
				printdp(dp);
				printf("[]\n");
			} else {
				printdp(dp);
				printf("[\n");
				for(int j = 0; j < num; j++)
				{
					_printNbt(data+j*8, print_load, dp+1);
				}
				printdp(dp);
				printf("]\n");
			}
			
		}
		*/
		this_tag = this_tag -> next;
		if(this_tag == NULL)
			break;
	}

	return 0;
}


