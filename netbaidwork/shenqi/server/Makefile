SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SOURCES))
ELF:=server
CC:=gcc
CFLAGS:= 
$(ELF):$(OBJS)
		 gcc $^ -o $@ -pthread  -I /usr/include/mysql/ -lmysqlclient
clean:
	  rm -rf $(OBJS) $(ELF)
