#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

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

int (*printNbtsLoad[NBT_NUM])(nbt_tag this_tag) = 
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
#elif
	return 0;
#endif
}
	

int _printNbt(nbt this_nbt, int print_load, int dp)
{
	nbt_tag this_tag = (nbt_tag)(this_nbt);
	for(int i = 0; i < 9999; i++)
	{
		printdp(dp);
		printfDebug(1, "%d %s", i, TAG_NAME[this_tag->tag_id]);
		printf("%s : ", this_tag -> name);
		printNbtLoad(this_tag);
		printf("\n");
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

		this_tag = this_tag -> next;
		if(this_tag == NULL)
			break;
	}

	return 0;
}

int printNbtLoad(nbt_tag this_tag)
{
	return printNbtsLoad[this_tag->tag_id](this_tag);
}

int printByte(nbt_tag this_tag)
{
	printf("%d", *(int8_t *)(this_tag->data));
	return 0;
}
int printShort(nbt_tag this_tag)
{
	printf("%d", (int16_t)ntohs(*(uint16_t *)(this_tag->data)));
	return 0;
}
int printInt(nbt_tag this_tag)
{
	printf("%d", (int32_t)ntohl(*(uint32_t *)(this_tag->data)));
	return 0;
}
int printLong(nbt_tag this_tag)
{
	printf("%lld", (int64_t)ntohll(*(uint64_t *)(this_tag->data)));
	return 0;
}
int printFloat(nbt_tag this_tag)
{
	printf("%f", (float)ntohl(*(uint32_t *)(this_tag->data)));
	return 0;
}
int printDouble(nbt_tag this_tag)
{
	printf("%f", (double)ntohll(*(uint64_t *)(this_tag->data)));
	return 0;
}
int printByteArray(nbt_tag this_tag)
{
	return -1;
}
int printString(nbt_tag this_tag)
{
	return -1;
}
int printList(nbt_tag this_tag)
{
	return -1;
}
int printCompound(nbt_tag this_tag)
{
	return -1;
}
int printIntArray(nbt_tag this_tag)
{
	return -1;
}
int printLongArray(nbt_tag this_tag)
{
	return -1;
}
