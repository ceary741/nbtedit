#ifndef __PRINT_NBT_H__
#define __PRINT_NBT_H__

#include "nbt.h"

int printByte(nbt_pointer *pseek);
int printShort(nbt_pointer *pseek);
int printInt(nbt_pointer *pseek);
int printLong(nbt_pointer *pseek);
int printFloat(nbt_pointer *pseek);
int printDouble(nbt_pointer *pseek);
int printByteArray(nbt_pointer *pseek);
int printString(nbt_pointer *pseek);
int printList(nbt_pointer *pseek);
int printCompound(nbt_pointer *pseek);
int printIntArray(nbt_pointer *pseek);
int printLongArray(nbt_pointer *pseek);

int printNbt(nbt this_nbt, int print_load);
int _printNbt(nbt this_nbt, int print_load, int dp);
nbt_load printNbtLoad(nbt_tag this_tag, nbt_pointer *seek);


#endif
