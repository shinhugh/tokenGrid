/*
 * Refer to tokenGrid.h for descriptions.
 */

#include <stdlib.h>
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



}

// ------------------------------------------------------------

tokenGrid * tokGd_tokenizeStr(const char *str, const char *tokenSeparator,
const char *lineSeparator) {

  tokenGrid *result;
  unsigned int startIndex, currIndex;
  unsigned int sepIndex;

  result = malloc(sizeof(tokenGrid));
  result->totalCount = 0;
  startIndex = 0;
  currIndex = 0;

  while(str[currIndex]) {
    if(str[currIndex] == lineSeparator[0]) {
      sepIndex = 0;
      while(str[currIndex + sepIndex] == lineSeparator[sepIndex]) {
        if(lineSeparator[sepIndex + 1] == 0) {
          // TODO
          currIndex += sepIndex;
          break;
        }
        sepIndex++;
      }
    }
    else if(str[currIndex] == tokenSeparator[0]) {
      sepIndex = 0;
      while(str[currIndex + sepIndex] == tokenSeparator[sepIndex]) {
        if(tokenSeparator[sepIndex + 1] == 0) {
          // TODO
          currIndex += sepIndex;
          break;
        }
        sepIndex++;
      }
    }
    else {
      // TODO
    }
    currIndex++;
  }

  return result;

}

// ------------------------------------------------------------

const char * tokGd_getToken_coor(const tokenGrid *grid, unsigned int lineIndex,
unsigned int inlineIndex) {



}

// ------------------------------------------------------------

const char * tokGd_getToken_index(const tokenGrid *grid, unsigned int index) {



}

// ------------------------------------------------------------

unsigned int tokGd_getTotalCount(const tokenGrid *grid) {



}

// ------------------------------------------------------------

unsigned int tokGd_getLineCount(const tokenGrid *grid) {



}

// ------------------------------------------------------------

unsigned int tokGd_getLineTokenCount(const tokenGrid *grid,
unsigned int lineIndex) {



}

// ------------------------------------------------------------

void tokGd_cleanup(tokenGrid *grid) {



}

// ------------------------------------------------------------
