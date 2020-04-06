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

// Helper struct and functions for dynamic string

typedef struct dynamicString {
  char *str;
  unsigned int length;
  unsigned int alloc_size;
} dynamicString;

void dyStr_appendChar(dynamicString *dyStr, char c);
void dyStr_appendStr(dynamicString *dyStr, char *s);
void dyStr_fit(dynamicString *dyStr);
void dyStr_initialize(dynamicString *dyStr);
void dyStr_deinitialize(dynamicString *dyStr);

// ------------------------------------------------------------

tokenGrid * tokGd_tokenizeFile(FILE *file, const char *tokenSeparator,
const char *lineSeparator) {

  // TODO
  return 0;

}

// ------------------------------------------------------------

tokenGrid * tokGd_tokenizeStr(const char *str, const char *tokenSeparator,
const char *lineSeparator) {

  tokenGrid *result;
  dynamicArray *lines;
  char *newToken;
  unsigned int startIndex, currIndex;
  unsigned int sepIndex;

  result = malloc(sizeof(tokenGrid));
  result->tokens = malloc(sizeof(dynamicArray));
  result->totalCount = 0;
  lines = (dynamicArray*) result->tokens;
  dyArr_appendElement(lines, malloc(sizeof(dynamicArray)));
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
    free(dyArr_getElement(lines, dyArr_getCount(lines) - 1));
    dyArr_removeElement(lines, dyArr_getCount(lines) - 1);
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
    free(dyArr_getElement(lines, i));
  }
  free(lines);
  free(grid);

}

// ------------------------------------------------------------
