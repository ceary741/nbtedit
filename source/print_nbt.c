#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <arpa/inet.h>

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

int (*printNbtsLoad[NBT_NUM])(nbt_load data) = 
{
//	[TAG_END]			=	printEnd,
	[TAG_BYTE]			=	printByte,
	[TAG_SHORT]			=	printShort,
	[TAG_INT]			=	printInt,
	[TAG_LONG]			=	printLong,
	[TAG_FLOAT]			=	printFloat,
	[TAG_DOUBLE]		=	printDouble,
	[TAG_BYTEARRAY]		=	printByteArray,
	[TAG_STRING]		=	printString,
	[TAG_LIST]			=	printList,
	[TAG_COMPOUND]		=	printCompound,
	[TAG_INTARRAY]		=	printIntArray,
	[TAG_LONGARRAY]		=	printLongArray,
};

#ifdef Linux
static uint64_t htonll(uint64_t val)
{
	return (((uint64_t) htonl(val)) << 32) + htonl(val >> 32);
}

static uint64_t ntohll(uint64_t val)
{
	return (((uint64_t) ntohl(val)) << 32) + ntohl(val >> 32);
}
#endif

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

int printfDebug(int ifhl, const char * restrict format, ...)
{
#ifdef DEBUG
	va_list argp;
	va_start(argp, format);
	if(ifhl)
		printf("DEBUG MSG: *");
	else
		printf("DEBUG MSG: ");
	int res = vprintf(format, argp);
	va_end(argp);
	if(ifhl)
		printf("* ");
	return res;
#else
	return 0;
#endif
}
	
int _printNbt(nbt this_nbt, int print_load, int dp)
{
	nbt_tag this_tag = (nbt_tag)(this_nbt);
	for(int i = 0; i < 9999; i++)
	{
		if(i != 0)
			printf(",\n");
		printdp(dp);
		printfDebug(1, "%d %s", i, TAG_NAME[this_tag->tag_id]);
		if(this_tag -> name)
			printf("%s : ", this_tag -> name);
		printNbtLoad(this_tag);
		void *data = this_tag -> data;
		if(this_tag -> tag_id == TAG_COMPOUND)
		{
			if(this_tag -> data == NULL)
			{
				printf("{}");
			} else {
				printf("\n");
				printdp(dp);
				printf("{\n");
				_printNbt(this_tag -> data, print_load, dp+1);
				printdp(dp);
				printf("}");
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
				printf("\n");
				printdp(dp);
				printf("[\n");
				for(int j = 0; j < num; j++)
				{
					printdp(dp);
					printf("{\n");
					_printNbt((nbt)*(uint64_t*)(data+j*8), print_load, dp+1);
					printdp(dp);
					printf("}");
					if(j == num-1)
						printf("\n");
					else
						printf(",\n");
				}
				printdp(dp);
				printf("]");
			}
		}

		this_tag = this_tag -> next;
		if(this_tag == NULL)
		{
			printf("\n");
			break;
		}
	}

	return 0;
}

int printNbtLoad(nbt_tag this_tag)
{
	return printNbtsLoad[this_tag->tag_id](this_tag->data);
}

int printByte(nbt_load data)
{
	printf("%dB", *(int8_t *)(data));
	return 0;
}
int printShort(nbt_load data)
{
	printf("%dS", (int16_t)ntohs(*(uint16_t *)(data)));
	return 0;
}
int printInt(nbt_load data)
{
	printf("%d", (int32_t)ntohl(*(uint32_t *)(data)));
	return 0;
}
int printLong(nbt_load data)
{
	printf("%ldL", (int64_t)ntohll(*(uint64_t *)(data)));
	return 0;
}
int printFloat(nbt_load data)
{
	float num;
	uint8_t *src = data;
	uint8_t *dst = &num;
	*dst = *(src+3);
	*(dst+1) = *(src+2);
	*(dst+2) = *(src+1);
	*(dst+3) = *src;
	printf("%fF", num);
	return 0;
}
int printDouble(nbt_load data)
{
	double num;
	uint8_t *src = data;
	uint8_t *dst = &num;
	*dst = *(src+7);
	*(dst+1) = *(src+6);
	*(dst+2) = *(src+5);
	*(dst+3) = *(src+4);
	*(dst+4) = *(src+3);
	*(dst+5) = *(src+2);
	*(dst+6) = *(src+1);
	*(dst+7) = *src;
	printf("%fD", num);
	return 0;
}
int printByteArray(nbt_load data)
{
	int len = (int32_t)ntohl(*(uint32_t *)(data));
	printf("[B;");
	for(int i = 0; i < len; i++)
	{
		printByte(data+4+i);
		if(i < len - 1)
			printf(",");
	}
	printf("]");
	return 0;
}
int printString(nbt_load data)
{
	int len = (int32_t)ntohl(*(uint32_t *)(data));
	printf("\"%s\"", (char *)data + 2);
	return 0;
}
int printList(nbt_load data)
{
	int tag_id = *(uint8_t *)data;
	if(tag_id == TAG_COMPOUND)
		return 0;
	int len = *(int32_t *)(data+1);
	printf("[");
	for(int i = 0; i < len; i++)
	{
		printNbtsLoad[tag_id](*(nbt_load *)(data+5+i*8));
		if(i < len - 1)
			printf(",");
	}
	printf("]");
	return 0;
}
int printCompound(nbt_load data)
{
	return 0;
}
int printIntArray(nbt_load data)
{
	int len = (int32_t)ntohl(*(uint32_t *)(data));
	printf("[I;");
	for(int i = 0; i < len; i++)
	{
		printInt(data+4+4*i);
		if(i < len - 1)
			printf(",");
	}
	printf("]");
	return 0;
}
int printLongArray(nbt_load data)
{
	int len = (int32_t)ntohl(*(uint32_t *)(data));
	printf("[L;");
	for(int i = 0; i < len; i++)
	{
		printInt(data+4+8*i);
		if(i < len - 1)
			printf(",");
	}
	printf("]");
	return 0;
}

