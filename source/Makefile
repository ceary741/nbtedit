CC = gcc
LD = gcc

OBJS = \
	get_chunk.o \
	cnbt.o \
	print_nbt.o 

#SRC = $(patsubst %.o, %.c, $(OBJS))

LDFLAGS = -lz
CCFLAGS = -g 

ifeq ($(shell uname),Linux)
CCFLAGS += -DLinux
endif
ifeq ($(shell uname),Darwin)
CCFLAGS += -DMacOs
endif
CCFLAGS += -DDEBUG

cnbt_Test : cnbt_Test.o $(OBJS) 
	$(CC) $(CCFLAGS) $^ $(LDFLAGS) -o $@

cnbt_Test_Debug : cnbt_Test.o $(OBJS) 
	$(CC) $(CCFLAGS) $^ $(LDFLAGS) -o $@

getChunk_Test : getChunk_Test.o $(OBJS) 
	$(CC) $(CCFLAGS) $^ $(LDFLAGS) -o $@

%.o : %.c %.h nbt.h
	$(CC) $(CCFLAGS) -c $< -o $@

%.o : %.c nbt.h
	$(CC) $(CCFLAGS) -c $< -o $@

clean :
	rm -rf *.o getChunk_Test cnbt_Test
