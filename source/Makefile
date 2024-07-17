CC = gcc
LD = gcc

OBJS = \
	cnbt.o \
	print_nbt.o \
	parse_snbt.o \
	ulib.o \
	get_chunk.o \

#SRC = $(patsubst %.o, %.c, $(OBJS))

LDFLAGS = -lz
CFLAGS = -g -O0

ifeq ($(shell uname),Linux)
CCFLAGS += -DLinux
endif
ifeq ($(shell uname),Darwin)
CCFLAGS += -DMacOs
endif
#CCFLAGS += -DDEBUG

parse_snbt_Test : parse_snbt_Test.o $(OBJS) 
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

cnbt_Test : cnbt_Test.o $(OBJS) 
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

get_chunk_Test : get_chunk_Test.o $(OBJS) 
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

%.o : %.c %.h nbt.h
	$(CC) $(CFLAGS) -c $< -o $@

#%.o : %.c nbt.h
#	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf *.o *_Test 
