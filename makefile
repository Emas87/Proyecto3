all: main

main: main.c
	gcc main.c -o main -g -W `pkg-config --cflags --libs gtk+-3.0 `

clean:
	rm Productor Consumidor Creador Finalizador
