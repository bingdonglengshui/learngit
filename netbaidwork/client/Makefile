SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SOURCES))
ELF:=client
CC:=gcc
CFLAGS:=
$(ELF):$(OBJS)
		   gcc $^ -o $@ -lcrypt -lcrypto -lpthread
clean:
	   rm -rf $(OBJS) $(ELF)
