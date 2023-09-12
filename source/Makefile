CC = gcc
LD = ld

OBJS = \
	get_chunk.o \
	chunk_structed.o \
	print_chunk.o 

SRC = $(patsubst %.o, %.c, $(OBJS))

LDFLAGS = -lz

chunkStruct_Test : chunkStruct_Test.o $(OBJS) 
	$(CC) $(OBJS) $< $(LDFLAGS) -o $@

getChunk_Test : getChunk_Test.o $(OBJS) 
	$(CC) $(OBJS) $< $(LDFLAGS) -o $@

%.o : %.c nbt.h
	$(CC) -c $< -o $@

clean :
	rm -rf *.o getChunk_Test chunkStruct_Test
