/*
 * Refer to tokenGrid.h for descriptions.
 */

#include <stdlib.h>
#include <string.h>
#include "dynamicArray.h"
#include "tokenGrid.h"

#define INITIAL_STR_SIZE 32
#define STR_SIZE_MULT 2

// ------------------------------------------------------------

// DEBUG FUNCTION
void printState(dynamicArray *array);

// ------------------------------------------------------------

tokenGrid * tokGd_tokenizeFile(FILE *file, const char *tokenSeparator,
const char *lineSeparator, unsigned char noEmptyToken) {

  // TODO
  return 0;

}

// ------------------------------------------------------------

tokenGrid * tokGd_tokenizeStr(const char *str, const char *tokenSeparator,
const char *lineSeparator, unsigned char noEmptyToken) {

  unsigned int i, j;
  tokenGrid *result;
  dynamicArray *lines;
  char *newToken;
  unsigned int startIndex, currIndex;
  unsigned int sepIndex;

  result = malloc(sizeof(tokenGrid));
  result->tokens = malloc(sizeof(dynamicArray));
  result->totalCount = 0;
  lines = (dynamicArray*) result->tokens;
  dyArr_initialize(lines);
  dyArr_appendElement(lines, malloc(sizeof(dynamicArray)));
  dyArr_initialize(dyArr_getElement(lines, dyArr_getCount(lines) - 1));
  startIndex = 0;
  currIndex = 0;

  while(str[currIndex]) {
    if(str[currIndex] == lineSeparator[0]) {
      sepIndex = 0; // TODO: edge case: currIndex - startIndex == 0
      while(str[currIndex + sepIndex] == lineSeparator[sepIndex]) {
        if(lineSeparator[sepIndex + 1] == 0) {
          newToken = malloc(currIndex - startIndex + 1);
          memcpy(newToken, str + startIndex, currIndex - startIndex);
          newToken[currIndex - startIndex] = 0;
          dyArr_appendElement(
          dyArr_getElement(lines, dyArr_getCount(lines) - 1), newToken);
          dyArr_appendElement(lines, malloc(sizeof(dynamicArray)));
          dyArr_initialize(dyArr_getElement(lines, dyArr_getCount(lines) - 1));
          result->totalCount++;
          currIndex += sepIndex;
          startIndex = currIndex + 1;
          break;
        }
        sepIndex++;
      }
    }
    else if(str[currIndex] == tokenSeparator[0]) {
      sepIndex = 0; // TODO: edge case: currIndex - startIndex == 0
      while(str[currIndex + sepIndex] == tokenSeparator[sepIndex]) {
        if(tokenSeparator[sepIndex + 1] == 0) {
          newToken = malloc(currIndex - startIndex + 1);
          memcpy(newToken, str + startIndex, currIndex - startIndex);
          newToken[currIndex - startIndex] = 0;
          dyArr_appendElement(
          dyArr_getElement(lines, dyArr_getCount(lines) - 1), newToken);
          result->totalCount++;
          currIndex += sepIndex;
          startIndex = currIndex + 1;
          break;
        }
        sepIndex++;
      }
    }
    currIndex++;
  }

  if(currIndex != startIndex) {
    newToken = malloc(currIndex - startIndex + 1);
    memcpy(newToken, str + startIndex, currIndex - startIndex);
    newToken[currIndex - startIndex] = 0;
    dyArr_appendElement(
    dyArr_getElement(lines, dyArr_getCount(lines) - 1), newToken);
    result->totalCount++;
  }

  if(dyArr_getCount(dyArr_getElement(lines, dyArr_getCount(lines) - 1)) == 0) {
    dyArr_deinitialize(dyArr_getElement(lines, dyArr_getCount(lines) - 1));
    free(dyArr_getElement(lines, dyArr_getCount(lines) - 1));
    dyArr_removeElement(lines, dyArr_getCount(lines) - 1);
  }

  if(noEmptyToken) {
    for(i = 0; i < dyArr_getCount(lines); i++) {
      for(j = 0; j < dyArr_getCount(dyArr_getElement(lines, i)); j++) {
        if(((char*) dyArr_getElement(dyArr_getElement(lines, i), j))[0] == 0) {
          dyArr_removeElement(dyArr_getElement(lines, i), j);
          result->totalCount--;
          j--;
        }
      }
    }
    for(i = 0; i < dyArr_getCount(lines); i++) {
      if(dyArr_getCount(dyArr_getElement(lines, i)) == 0) {
        dyArr_deinitialize(dyArr_getElement(lines, i));
        free(dyArr_getElement(lines, i));
        dyArr_removeElement(lines, i);
        i--;
      }
    }
  }

  return result;

}

// ------------------------------------------------------------

const char * tokGd_getToken_coor(const tokenGrid *grid, unsigned int lineIndex,
unsigned int inlineIndex) {

  dynamicArray *lines;

  lines = (dynamicArray*) grid->tokens;

  if(lineIndex >= dyArr_getCount(lines)) {
    // TODO
  }
  if(inlineIndex >= dyArr_getCount(dyArr_getElement(lines, lineIndex))) {
    // TODO
  }

  return dyArr_getElement(dyArr_getElement(lines, lineIndex), inlineIndex);

}

// ------------------------------------------------------------

const char * tokGd_getToken_index(const tokenGrid *grid, unsigned int index) {

  unsigned int i;
  dynamicArray *lines;
  unsigned int currIndex, currLineLength;

  lines = (dynamicArray*) grid->tokens;

  if(index >= grid->totalCount) {
    // TODO
  }

  currIndex = 0;
  for(i = 0; i < dyArr_getCount(lines); i++) {
    currLineLength = dyArr_getCount(dyArr_getElement(lines, i));
    if(currIndex + currLineLength > index) {
      return dyArr_getElement(dyArr_getElement(lines, i), (index - currIndex));
    }
    currIndex += currLineLength;
  }

}

// ------------------------------------------------------------

unsigned int tokGd_getTotalCount(const tokenGrid *grid) {

  return grid->totalCount;

}

// ------------------------------------------------------------

unsigned int tokGd_getLineCount(const tokenGrid *grid) {

  dynamicArray *lines;

  lines = (dynamicArray*) grid->tokens;

  return dyArr_getCount(lines);

}

// ------------------------------------------------------------

unsigned int tokGd_getLineTokenCount(const tokenGrid *grid,
unsigned int lineIndex) {

  dynamicArray *lines;

  lines = (dynamicArray*) grid->tokens;

  if(lineIndex >= dyArr_getCount(lines)) {
    // TODO
  }

  return dyArr_getCount(dyArr_getElement(lines, lineIndex));

}

// ------------------------------------------------------------

void tokGd_cleanup(tokenGrid *grid) {

  unsigned int i, j;
  dynamicArray *lines;

  lines = (dynamicArray*) grid->tokens;

  for(i = 0; i < dyArr_getCount(lines); i++) {
    for(j = 0; j < dyArr_getCount(dyArr_getElement(lines, i)); j++) {
      free(dyArr_getElement(dyArr_getElement(lines, i), j));
    }
    dyArr_deinitialize(dyArr_getElement(lines, i));
    free(dyArr_getElement(lines, i));
  }
  dyArr_deinitialize(lines);
  free(lines);
  free(grid);

}

// ------------------------------------------------------------

// DEBUG FUNCTION
void printState(dynamicArray *array) {

  unsigned int i, j;

  for(i = 0; i < dyArr_getCount(array); i++) {
    for(j = 0; j < dyArr_getCount(dyArr_getElement(array, i)); j++) {
      printf("(%d, %d): %s\n", i, j,
      (char*) dyArr_getElement(dyArr_getElement(array, i), j));
    }
  }

}
