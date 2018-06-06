SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SOURCES))
ELF:=main
CC:=gcc
 CFLAGS:= -Wall -lpthread -lcrypt -lcrypto
$(ELF):$(OBJS)
		 gcc $^ -o $@
clean:
	 rm -rf $(OBJS) $(ELF)

