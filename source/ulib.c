#include "ulib.h"
#include "nbt.h"

void reverse_16(void *num) 
{
	char buf[2];
	char *n = num;
	buf[0] = n[1];
	buf[1] = n[0];
	*(uint16_t*)num = *(uint16_t*)buf;
	return;
}

void reverse_32(void *num) 
{
	char buf[4];
	char *n = num;
	buf[0] = n[3];
	buf[1] = n[2];
	buf[2] = n[1];
	buf[3] = n[0];
	*(uint32_t*)num = *(uint32_t*)buf;
	return;
}

void reverse_64(void *num) 
{
	char buf[8];
	char *n = num;
	buf[0] = n[7];
	buf[1] = n[6];
	buf[2] = n[5];
	buf[3] = n[4];
	buf[4] = n[3];
	buf[5] = n[2];
	buf[6] = n[1];
	buf[7] = n[0];
	*(uint64_t*)num = *(uint64_t*)buf;
	return;
}
