IDIR =.
ODIR=.
LDIR =./lib

CC=gcc
CFLAGS=-I$(IDIR) -Wall -g -ldl
#CFLAGS+= `pkg-config --cflags --libs glib-2.0`  -lgcrypt


_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ := $(patsubst %.c, %.o, $(wildcard *.c))
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

target = main

$(target): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean lib cleanlib

lib:
	gcc -fpic -shared lib/libtest.c -o lib/libtest.so

cleanlib:
	rm -f lib/libtest.so

clean:
	rm -f *.o *~ core $(INCDIR)/*~ $(target)
