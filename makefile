# Compiler
CC = gcc
# dynamicArray path
DYARR_PATH = lib/dynamicArray
# Targets to make
TARGETS = libtokenGrid.a tokenGrid.o $(DYARR_PATH)/dynamicArray.o test.out

all: libtokenGrid.a

# Make static library tokenGrid
libtokenGrid.a: tokenGrid.o $(DYARR_PATH)/dynamicArray.o
	ar rcs $@ $^

# Make tokenGrid.o
tokenGrid.o: tokenGrid.c tokenGrid.h $(DYARR_PATH)/dynamicArray.h
	$(CC) -c -o $@ $< -I . -I $(DYARR_PATH)

# Make dynamicArray.o
lib/dynamicArray/dynamicArray.o: $(DYARR_PATH)/dynamicArray.c $(DYARR_PATH)/dynamicArray.h
	$(CC) -c -o $@ $< -I $(DYARR_PATH)

# Make test program
test: test/test.c libtokenGrid.a
	$(CC) -o test.out $< -I . -I $(DYARR_PATH) -L . -L $(DYARR_PATH) -l tokenGrid

.PHONY: clean

# Remove all but source code
clean:
	rm -rf $(TARGETS)
