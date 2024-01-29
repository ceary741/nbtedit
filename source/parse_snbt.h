#ifndef __PARSE_SNBT_H__
#define __PARSE_SNBT_H__


static int isNumChar(char c);
static int isNumStart(char c);
static int readChar(char **seek, char c, char *snbt_end);
static char* searchChar(char *seek, char* charlist, char *snbt_end);
static int seekNoSpace(char **seek, char *snbt_end);
static int rseekNoSpace(char **seek, char *snbt_end);
static char *rtrim(char *str);
static int addToRoot(nbt_tag this_nbt, nbt_tag root);

static nbt _ParseSnbt(char **seek, nbt root, char *snbt, char *snbt_end);

nbt nbt_ParseSnbt(char *snbt, uint64_t size, uint64_t *error);

#endif
