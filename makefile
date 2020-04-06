# Compiler
CC = gcc
# Compiler flags
CFLAGS = -I . -I lib/dynamicArray -L . -L lib/dynamicArray
# Targets to make
TARGETS = libtokenGrid.a tokenGrid.o lib/dynamicArray/dynamicArray.o

all: libtokenGrid.a

# Make static library tokenGrid
libtokenGrid.a: tokenGrid.o lib/dynamicArray/dynamicArray.o
	ar rcs $@ $^

# Make tokenGrid.o
tokenGrid.o: tokenGrid.c tokenGrid.h lib/dynamicArray/dynamicArray.h
	$(CC) -c -o $@ $< -I . -I lib/dynamicArray

# Make dynamicArray.o
lib/dynamicArray/dynamicArray.o: lib/dynamicArray/dynamicArray.c lib/dynamicArray/dynamicArray.h
	$(CC) -c -o $@ $< -I lib/dynamicArray

# Make test program
test: test/test.c libtokenGrid.a
	$(CC) $< -I . -I lib/dynamicArray -l tokenGrid

.PHONY: clean

# Remove all but source code
clean:
	rm $(TARGETS)
