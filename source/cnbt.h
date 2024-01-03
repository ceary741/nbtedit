#ifndef __CNBT_H__
#define __CNBT_H__

#include "nbt.h"

extern nbt_load (*readNbtsLoad[NBT_NUM])(nbt_pointer *pseek);

static nbt_load readByte(nbt_pointer *pseek);
static nbt_load readShort(nbt_pointer *pseek);
static nbt_load readInt(nbt_pointer *pseek);
static nbt_load readLong(nbt_pointer *pseek);
static nbt_load readFloat(nbt_pointer *pseek);
static nbt_load readDouble(nbt_pointer *pseek);
static nbt_load readByteArray(nbt_pointer *pseek);
static nbt_load readString(nbt_pointer *pseek);
static nbt_load readList(nbt_pointer *pseek);
static nbt_load readCompound(nbt_pointer *pseek);
static nbt_load readIntArray(nbt_pointer *pseek);
static nbt_load readLongArray(nbt_pointer *pseek);

nbt chunkStructed(chunk_data data);
static nbt_tag nextTag(nbt_tag *plast_next, nbt_pointer *seek);
static nbt_tag readNbtHead(nbt_pointer *seek);
static nbt_load readNbtLoad(nbt_tag this_tag, nbt_pointer *seek);

int freeChunk(nbt data);

int nbt_GetArraySize(const nbt array);
int nbt_GetArrayItem(const nbt array, int index, uint64_t *value);
nbt nbt_GetItemOfName(const nbt this_nbt, const char* name);
nbt nbt_GetItemOfIndex(const nbt this_nbt, int index);
//nbt nbt_GetNextItem(const nbt const this_nbt);
//int nbt_GetSize(const nbt const this_nbt);
//int nbt_HasItem(const nbt this_nbt, const char *string);
//
//char *nbt_GetName(const nbt const item);
//int nbt_GetTagId(const nbt const item);
//double nbt_GetNumberValue(const nbt const item);
//
//nbt_tag nbt_Create*();
//
//int nbt_AddItemToArray(uint64_t item);
//int nbt_AddItemToList(void *load);
//int nbt_AddItemToCompound(const nbt);
//
//uint64_t nbt_DetachFromArray(int index);
//void* nbt_DetachFromList(int index);
//nbt nbt_DetachFromCompoundOfIndex(int index);
//nbt nbt_DetachFromCompoundOfName(const char * const name);
//
//nbt nbt_Duplicate(const nbt item, int recurse);
//nbt nbt_Compare(const nbt const a, const nbt const b, const int case_sensitive);
//
#endif
