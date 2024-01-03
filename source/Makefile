CC = gcc
LD = ld

OBJS = \
	get_chunk.o \
	cnbt.o \
	print_nbt.o 

SRC = $(patsubst %.o, %.c, $(OBJS))

LDFLAGS = -lz

cnbt_Test : cnbt_Test.o $(OBJS) 
	$(CC) $(OBJS) $< $(LDFLAGS) -o $@

getChunk_Test : getChunk_Test.o $(OBJS) 
	$(CC) $(OBJS) $< $(LDFLAGS) -o $@

%.o : %.c %.h nbt.h
	$(CC) -c $< -o $@

clean :
	rm -rf *.o getChunk_Test cnbt_Test
