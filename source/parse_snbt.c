#include <stdio.h>
#include <stdlib.h>

#include "nbt.c"
#include "parse_snbt.h"

char buf[4096];

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

nbt nbt_ParseSnbt(char *snbt)
{
	malloc
	

nbt _ParseSnbt(char *snbt, nbt root)
{
	while()
	{
		readname();
		create_nbt_tag();
		read();
		if(list)
		{
			readList(char *, nbt);
		}
		isLast();
	}



	


