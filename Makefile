CC=gcc
CFLAGS=-Wall --std=c99 
OBJECTS=./build/vector.o ./build/my_string.o ./build/node.o ./build/word_linked_list.o ./build/game_print.o ./build/user_input.o

main: ./src/main.c $(OBJECTS)
	$(CC) $(CFLAGS) ./src/main.c $(OBJECTS) -o play_evil_hangman

./build/vector.o: ./src/data_types/vector/vector.c
	$(CC) $(CFLAGS) -c -o $@ $<

./build/my_string.o: ./src/data_types/my_string/my_string.c
	$(CC) $(CFLAGS) -c -o $@ $<

./build/node.o: ./src/data_types/word_linked_list/node.c
	$(CC) $(CFLAGS) -c -o $@ $<

./build/word_linked_list.o: ./src/data_types/word_linked_list/word_linked_list.c
	$(CC) $(CFLAGS) -c -o $@ $<

./build/game_print.o: ./src/ui/game_print.c
	$(CC) $(CFLAGS) -c -o $@ $<

./build/user_input.o: ./src/user_input/user_input.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f play_evil_hangman ./build/*.o
