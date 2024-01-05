#ifndef __PRINT_NBT_H__
#define __PRINT_NBT_H__

#include "nbt.h"

int printByte(nbt_tag this_tag);
int printShort(nbt_tag this_tag);
int printInt(nbt_tag this_tag);
int printLong(nbt_tag this_tag);
int printFloat(nbt_tag this_tag);
int printDouble(nbt_tag this_tag);
int printByteArray(nbt_tag this_tag);
int printString(nbt_tag this_tag);
int printList(nbt_tag this_tag);
int printCompound(nbt_tag this_tag);
int printIntArray(nbt_tag this_tag);
int printLongArray(nbt_tag this_tag);

int printNbtLoad(nbt_tag this_tag);

int printNbt(nbt this_nbt, int print_load);
int _printNbt(nbt this_nbt, int print_load, int dp);
int printfDebug(int ifhl, const char * restrict format, ...);
int printdp(int dp);


#endif
