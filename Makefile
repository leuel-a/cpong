CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
LIB = -lraylib -lm -lX11
OUTPUT = out

build: main.c
	$(CC) -o $(OUTPUT) main.c $(CFLAGS) $(LIB)

run: main.c
	./out
