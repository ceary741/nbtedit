CC = gcc
LD = gcc

OBJS = \
	get_chunk.o \
	cnbt.o \
	print_nbt.o 

#SRC = $(patsubst %.o, %.c, $(OBJS))

LDFLAGS = -lz

cnbt_Test : cnbt_Test.o $(OBJS) 
	$(CC) -g $^ $(LDFLAGS) -o $@

getChunk_Test : getChunk_Test.o $(OBJS) 
	$(CC) -g $(OBJS) $< $(LDFLAGS) -o $@

%.o : %.c %.h nbt.h
	$(CC) -g -c $< -o $@

%.o : %.c nbt.h
	$(CC) -g -c $< -o $@

clean :
	rm -rf *.o getChunk_Test cnbt_Test
