CC=gcc
CFLAGS=-O2 -Wall -Wextra
LDLIBS=-lrdkafka
producer: src/main.c
	$(CC) $(CFLAGS) -o producer src/main.c $(LDLIBS)
clean:
	rm -f producer
