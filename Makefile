CC=gcc
CFLAGS=-Wall --std=c99 
OBJECTS=./build/vector.o ./build/my_string.o ./build/game_print.o

main: ./src/main.c $(OBJECTS)
	$(CC) $(CFLAGS) ./src/main.c $(OBJECTS) -o string_driver

./build/vector.o: ./src/data_types/vector/vector.c
	$(CC) $(CFLAGS) -c -o $@ $<

./build/my_string.o: ./src/data_types/my_string/my_string.c
	$(CC) $(CFLAGS) -c -o $@ $<

./build/game_print.o: ./src/ui/game_print.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f string_driver ./build/*.o
