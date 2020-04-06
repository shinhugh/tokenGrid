# Compiler
CC = gcc
# Compiler flags
CFLAGS = -I . -L .
# Targets to make
TARGETS = libtokenGrid.a tokenGrid.o lib/dynamicArray/dynamicArray.o

all: libtokenGrid.a

# Make static library tokenGrid
libtokenGrid.a: tokenGrid.o lib/dynamicArray/dynamicArray.o
	ar rcs $@ $^

# Make tokenGrid.o
tokenGrid.o: tokenGrid.c tokenGrid.h lib/dynamicArray/dynamicArray.h
	$(CC) -c -o $@ $< $(CFLAGS)

# Make dynamicArray.o
lib/dynamicArray/dynamicArray.o: lib/dynamicArray/dynamicArray.c lib/dynamicArray/dynamicArray.h
	$(CC) -c -o $@ $< $(CFLAGS)

# Make test program
test: test/test.c libtokenGrid.a
	$(CC) $< $(CFLAGS) -l tokenGrid

.PHONY: clean

# Remove all but source code
clean:
	rm $(TARGETS)
