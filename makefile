CC=gcc
CFLAGS= -g -W `pkg-config --cflags --libs gtk+-3.0` -std=gnu99 -lm
DEPS = libs/matriz.h
all: main

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
   
main: main.o
	$(CC) main.c -o main $(CFLAGS)

clean:
	rm main *.o
