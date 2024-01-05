#ifndef __PRINT_NBT_H__
#define __PRINT_NBT_H__

#include "nbt.h"

int printByte(nbt_load data);
int printShort(nbt_load data);
int printInt(nbt_load data);
int printLong(nbt_load data);
int printFloat(nbt_load data);
int printDouble(nbt_load data);
int printByteArray(nbt_load data);
int printString(nbt_load data);
int printList(nbt_load data);
int printCompound(nbt_load data);
int printIntArray(nbt_load data);
int printLongArray(nbt_load data);

int printNbtLoad(nbt_tag this_tag);

int printNbt(nbt this_nbt, int print_load);
int _printNbt(nbt this_nbt, int print_load, int dp);
int printfDebug(int ifhl, const char * restrict format, ...);
int printdp(int dp);



#endif
