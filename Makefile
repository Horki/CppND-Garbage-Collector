CC=g++
FLAGS=-std=c++17 -Werror -g

BIN=gc

all: $(BIN)

gc: main.cpp gc_details.h gc_pointer.h gc_iterator.h LeakTester.h
	$(CC) $(FLAGS) -o $@ $<

clean:
	rm -If $(BIN)
