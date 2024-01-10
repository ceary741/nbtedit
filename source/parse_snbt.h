#ifndef __PARSE_SNBT_H__
#define __PARSE_SNBT_H__

nbt nbt_ParseSnbt(char *snbt, uint64_t size, uint64_t *error);
static nbt _ParseSnbt(char **seek, nbt root, char *snbt_end);

#endif
