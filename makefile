# Compiler
CC = gcc
# Compiler flags
CFLAGS = -g -Wall -I . -I $(PATH_DYARR) -I $(PATH_DYSTR) -L . -L $(PATH_DYARR) \
-L $(PATH_DYSTR)
# dynamicArray path
PATH_DYARR = lib/dynamicArray
# dynamicString path
PATH_DYSTR = lib/dynamicString
# Object files
OBJ = tokenGrid.o $(PATH_DYARR)/dynamicArray.o $(PATH_DYSTR)/dynamicString.o
# Header files
HEADERS = tokenGrid.h $(PATH_DYARR)/dynamicArray.h $(PATH_DYSTR)/dynamicString.h
# All possible targets
TARGETS = libtokenGrid.a $(OBJ) test

default: libtokenGrid.a

# Make static library tokenGrid
libtokenGrid.a: $(OBJ)
	ar rcs $@ $^

# Make tokenGrid.o
tokenGrid.o: tokenGrid.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Make object files
%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

# Make test program
test: tests/test.c tokenGrid.h libtokenGrid.a
	$(CC) -o $@ $< $(CFLAGS) -l tokenGrid

.PHONY: clean

# Remove all but source code
clean:
	rm -rf $(TARGETS)
