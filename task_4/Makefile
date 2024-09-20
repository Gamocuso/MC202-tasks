CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: batcomputador

batcomputador: batcomputador.o bat-memory.o
	gcc batcomputador.o bat-memory.o -g $(LDFLAGS) -o batcomputador

batcomputador.o: batcomputador.c bat-memory.h
	gcc $(CFLAGS) -c batcomputador.c

bat-memory.o: bat-memory.c bat-memory.h
	gcc -std=c99 -Wall -Werror -Wvla -c bat-memory.c

clean:
	rm -f batcomputador
