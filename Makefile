PROG1=	getmntdir
SRCS1=	getmntdir.c main.c
OBJS1 := $(SRCS1:.c=.o)

UNAME := $(shell uname)
ifeq ($(UNAME), FreeBSD) # XXX
CC=	clang
else
CC=	gcc
endif
CFLAGS+= -Wall -g

.PHONY: all clean

all: $(PROG1)
$(PROG1): $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $(OBJS1)
.c.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f ./*.o ./$(PROG1)
