#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

#include "nbt.h"
#include "parse_snbt.h"

char buf[4096];

#ifdef Linux
static uint64_t htonll(uint64_t val)
{
	return (((uint64_t) htonl(val)) << 32) + htonl(val >> 32);
}

static uint64_t ntohll(uint64_t val)
{
	return (((uint64_t) ntohl(val)) << 32) + ntohl(val >> 32);
}
#endif

static int isNumChar(char c)
{
	if(c == '-')
		return 1;
	if(c >= '0' && c <= '9')
		return 1;
	if(c == '.')
		return 1;
	return 0;
}

static int isNumStart(char c)
{
	if(c == '-')
		return 1;
	if(c >= '0' && c <= '9')
		return 1;
	return 0;
}

static int readChar(char **seek, char c, char *snbt_end)
{
	while(**seek != c)
	{
		if(*seek != snbt_end-1 && isspace(**seek))
		{
			(*seek) ++;
		} else {
			return -1;
		}
	}
	(*seek) ++;
	return 1;
}

static char* searchChar(char *seek, char* charlist, char *snbt_end)
{
	while(seek != snbt_end)
	{
		int find = 0;
		for(int i = 0; i < strlen(charlist); i++)
		{
			if(*seek == charlist[i])
			{
				find = 1;
				break;
			}
		}
		if(find == 1)
			break;
		seek ++;
	}
	return seek;
}

static int seekNoSpace(char **seek, char *snbt_end)
{
	while(*seek != snbt_end && isspace(**seek))
	{
		(*seek) ++;
	}
	return 1;
}

static int rseekNoSpace(char **seek, char *snbt_start)
{
	while(*seek != snbt_start && isspace(**seek))
	{
		(*seek) --;
	}
	return 1;
}

static char *rtrim(char *str) 
{ 
	if (str == NULL || *str == '\0') 
	{ 
		return str; 
	} 
	int len = strlen(str); 
	char *p = str + len - 1; 
	while (p >= str && isspace(*p)) 
	{ 
		*p = '\0'; --p; 
	} 
	return str; 
} 

static int addToRoot(nbt_tag this_nbt, nbt_tag root)
{
	nbt_tag next;
	if(root->tag_id != TAG_COMPOUND)
	{
		return -1;
	} else if(root->data == NULL)
	{
		root -> data = this_nbt;
		return 1;
	}

	next = root -> data;
	while(next->next != NULL)
	{
		next = next -> next;
	}
	next -> next = this_nbt;
	return -1;
}

nbt nbt_ParseSnbt(char *snbt, uint64_t size, uint64_t *error)
{
	char *seek = snbt;
	nbt root = malloc(sizeof(struct nbt_tag));
	root -> name_length = 0;
	root -> name = NULL;
	root -> tag_id = TAG_COMPOUND;
	root -> next = NULL;
	root -> data = NULL;

	if(readChar(&seek, '{', snbt+size) < 0)
	{
		*error = seek - snbt;
		free(root);
		return NULL;
	}

	while(1)
	{
		nbt_tag this_nbt = _ParseSnbt(&seek, root, snbt, snbt+size);
		addToRoot(this_nbt, root);
		int is_end = readChar(&seek, ',', snbt+size); //check res
		if(is_end == -1)
		{
			break;
		}
		//check }
	}

	return root;
}

static nbt _ParseSnbt(char **seek, nbt root, char *snbt, char *snbt_end)
{
	seekNoSpace(seek, snbt_end);
	char *name_end = searchChar(*seek, ":", snbt_end);
	//if(name_end == snbt_end)
	int name_len = name_end - *seek;
	strncpy(buf, *seek, name_len);
	buf[name_len] = '\0';
	rtrim(buf);

	nbt_tag this_nbt = malloc(sizeof(struct nbt_tag));
	this_nbt -> next = NULL;
	this_nbt -> name_length = (uint16_t)strlen(buf);
	this_nbt -> name = malloc(strlen(buf)+1);
	strncpy(this_nbt->name, buf, strlen(buf)+1);

	*seek = name_end;
	readChar(seek, ':', snbt_end); //check res
	seekNoSpace(seek, snbt_end);
	if(**seek == '\"')
	{
		this_nbt -> tag_id = TAG_STRING;
		char *str_end = searchChar((*seek)+1, "\"", snbt_end);
		if(str_end == snbt_end)
		{
			free(this_nbt -> name);
			free(this_nbt);
			return NULL;
		}
		this_nbt -> data = malloc(str_end-*seek);
		strncpy(this_nbt->data, (*seek)+1, str_end-*seek-1);
		((char *)(this_nbt->data))[str_end-*seek-1] = '\0';

		*seek = str_end + 1;
		return this_nbt;
	}

	else if(isNumStart(**seek))
	{
		nbt_tag res;
		char *num_end = searchChar(*seek, ",}", snbt_end);
		num_end--;
		rseekNoSpace(&num_end, snbt);

		switch(*num_end) {
			case 'b':
			case 'B':
				this_nbt -> tag_id = TAG_BYTE;
				this_nbt -> data = malloc(sizeof(int8_t));
				*(int8_t*)(this_nbt->data) = strtol(*seek, NULL, 10);
				res = this_nbt;
				break;
			case 's':
			case 'S':
				this_nbt -> tag_id = TAG_SHORT;
				this_nbt -> data = malloc(sizeof(int16_t));
				*(int16_t*)(this_nbt->data) = htons(strtol(*seek, NULL, 10));
				res = this_nbt;
				break;
			case 'l':
			case 'L':
				this_nbt -> tag_id = TAG_LONG;
				this_nbt -> data = malloc(sizeof(int64_t));
				*(int64_t*)(this_nbt->data) = htonll(strtoll(*seek, NULL, 10));
				res = this_nbt;
				break;
			case 'f':
			case 'F':
				this_nbt -> tag_id = TAG_FLOAT;
				this_nbt -> data = malloc(sizeof(float));
				float float_num = strtof(*seek, NULL);
				uint8_t *dst = this_nbt -> data;
				uint8_t *src = &float_num;
				*dst = *(src+3);
				*(dst+1) = *(src+3);
				*(dst+2) = *(src+2);
				*(dst+3) = *(src+1);
				res = this_nbt;
				break;
			case 'd':
			case 'D':
				this_nbt -> tag_id = TAG_DOUBLE;
				this_nbt -> data = malloc(sizeof(double));
				double double_num = strtod(*seek, NULL);
				int64_t *p_double_num = &double_num;
				*(double*)(this_nbt->data) = htonll(*p_double_num);
				res = this_nbt;
				break;
		}

		*seek = searchChar(*seek, ",}", snbt_end);
		return res;

	} else if(**seek == '[')
	{
		return NULL;
	} else if(**seek == '{')
	{
		return NULL;
	} else
	{
		return NULL;
	}
	return NULL;
}
