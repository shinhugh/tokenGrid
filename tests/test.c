#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenGrid.h"

void demonstrateTokenizeFile();
void demonstrateTokenizeStr();

// ------------------------------------------------------------

/*
 * Demonstrates tokenGrid library usage.
 */
int main() {

  // demonstrateTokenizeFile();
  demonstrateTokenizeStr();

}

// ------------------------------------------------------------

/*
 * Demonstrates tokenizeFile()
 */
void demonstrateTokenizeFile() {

  // Local variables
  unsigned int i, j;
  FILE *file;
  tokenGrid *grid;

  // Open test file
  file = fopen("./test.txt", "r");

  // Tokenize file
  grid = tokGd_tokenizeFile(file, " ", "\n", 1);

  // Close test file
  fclose(file);

  // Check for tokenization error (file was null, etc.)
  if(!grid) {
    fprintf(stderr, "Error: Tokenization unsuccessful.\n");
    return;
  }

  // Print contents of token grid by coordinates
  printf("Iteration by coordinates:\n");
  // Iterate through lines
  for(i = 0; i < tokGd_getLineCount(grid); i++) {
    // Iterate through tokens on line
    for(j = 0; j < tokGd_getLineTokenCount(grid, i); j++) {
      // Print token at these coordinates in the grid
      printf("|%s|", tokGd_getToken_coor(grid, i, j));
    }
    printf("\n");
  }

  // Print contents of token grid by overall index
  printf("Iteration by overall index:\n");
  // Iterate by overall index
  for(i = 0; i < tokGd_getTotalCount(grid); i++) {
    // Print token at this overall index in the grid
    printf("|%s|", tokGd_getToken_index(grid, i));
  }
  printf("\n");

  // Free memory used by token grid
  tokGd_cleanup(grid);

}

// ------------------------------------------------------------

/*
 * Demonstrates tokenizeStr()
 */
void demonstrateTokenizeStr() {

  // Local variables
  unsigned int i, j;
  char *str;
  tokenGrid *grid;

  // String to test on
  str = "first second  third\nfourth fifth\n\nsixth seventh";

  // Tokenize file
  grid = tokGd_tokenizeStr(str, " ", "\n", 1);

  // Check for tokenization error (file was null, etc.)
  if(!grid) {
    fprintf(stderr, "Error: Tokenization unsuccessful.\n");
    return;
  }

  // Print contents of token grid by coordinates
  printf("Iteration by coordinates:\n");
  // Iterate through lines
  for(i = 0; i < tokGd_getLineCount(grid); i++) {
    // Iterate through tokens on line
    for(j = 0; j < tokGd_getLineTokenCount(grid, i); j++) {
      // Print token at these coordinates in the grid
      printf("<%s>", tokGd_getToken_coor(grid, i, j));
    }
    printf("\n");
  }
  printf("\n");

  // Print contents of token grid by overall index
  printf("Iteration by overall index:\n");
  // Iterate by overall index
  for(i = 0; i < tokGd_getTotalCount(grid); i++) {
    // Print token at this overall index in the grid
    printf("<%s>", tokGd_getToken_index(grid, i));
  }
  printf("\n\n");

  // Free memory used by token grid
  tokGd_cleanup(grid);

}
