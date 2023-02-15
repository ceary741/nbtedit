#ifndef __NBT_H__
#define __NBT_H__

#define NBT_NUM 13
#define TAG_END			0
#define TAG_BYTE 		1
#define TAG_SHORT		2
#define TAG_INT			3
#define TAG_LONG		4
#define TAG_FLOAT		5
#define TAG_DOUBLE		6
#define TAG_BYTEARRAY	7
#define TAG_STRING		8
#define TAG_LIST		9
#define TAG_COMPOUND	10
#define TAG_INTARRAY	11
#define TAG_LONGARRAY	12

typedef void* chunk_data;

typedef void* nbt_pointer;

typedef void* nbt_load;

typedef struct nbt_tag
{
	struct nbt_tag* next;
	uint8_t tag_id;
	uint16_t name_length;
	char *name;
	nbt_load data;
} *nbt_tag;

typedef nbt_tag nbt;

typedef int8_t *byte_load;
typedef int16_t *short_load;
typedef int32_t *int_load;
typedef int64_t *long_load;
typedef float *float_load;
typedef double *double_load;

typedef struct byte_array_load
{
	int32_t size;
	int8_t value[0];
} *byte_array_load;

typedef struct int_array_load
{
	int32_t size;
	int32_t value[0];
} *int_array_load;

typedef struct long_array_load
{
	int32_t size;
	int64_t value[0];
} *long_array_load;

typedef struct string_load
{
	uint16_t length;
	char value[0];
} *string_load;

typedef nbt compound_load;

typedef void* list_value;
typedef struct list_load
{
	uint8_t tag_id;
	uint32_t size;
	list_value value[0];
} *list_load;

#endif
