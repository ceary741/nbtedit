#ifndef __CHUNK_STRUCTED_H__
#define __CHUNK_STRUCTED_H__

#include "nbt.h"

nbt_tag parseEnd(nbt_pointer nbtp);
nbt_tag parseByte(nbt_pointer nbtp);
nbt_tag parseShort(nbt_pointer nbtp);
nbt_tag parseInt(nbt_pointer nbtp);
nbt_tag parseLong(nbt_pointer nbtp);
nbt_tag parseFloat(nbt_pointer nbtp);
nbt_tag parseDouble(nbt_pointer nbtp);
nbt_tag parseByteArray(nbt_pointer nbtp);
nbt_tag parseString(nbt_pointer nbtp);
nbt_tag parseList(nbt_pointer nbtp);
nbt_tag parseCompound(nbt_pointer nbtp);
nbt_tag parseIntArray(nbt_pointer nbtp);
nbt_tag parseLongArray(nbt_pointer nbtp);


#endif
