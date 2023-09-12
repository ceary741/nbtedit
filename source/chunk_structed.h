#ifndef __CHUNK_STRUCTED_H__
#define __CHUNK_STRUCTED_H__

#include "nbt.h"

extern nbt_load (*readNbtsLoad[NBT_NUM])(nbt_pointer *pseek);

nbt_load readByte(nbt_pointer *pseek);
nbt_load readShort(nbt_pointer *pseek);
nbt_load readInt(nbt_pointer *pseek);
nbt_load readLong(nbt_pointer *pseek);
nbt_load readFloat(nbt_pointer *pseek);
nbt_load readDouble(nbt_pointer *pseek);
nbt_load readByteArray(nbt_pointer *pseek);
nbt_load readString(nbt_pointer *pseek);
nbt_load readList(nbt_pointer *pseek);
nbt_load readCompound(nbt_pointer *pseek);
nbt_load readIntArray(nbt_pointer *pseek);
nbt_load readLongArray(nbt_pointer *pseek);

nbt chunkStructed(chunk_data data);
nbt_tag nextTag(nbt_tag *plast_next, nbt_pointer *seek);
nbt_tag readNbtHead(nbt_pointer *seek);
nbt_load readNbtLoad(nbt_tag this_tag, nbt_pointer *seek);

int freeChunk(nbt data);


#endif
