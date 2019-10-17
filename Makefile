CC=gcc
CFLAGS=-Wall --std=c99 
DEPS=vector.o my_string.o game_print.o

main: main.c $(DEPS)
	$(CC) $(CFLAGS) main.c $(DEPS) -o string_driver

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	rm -f string_driver *.o
