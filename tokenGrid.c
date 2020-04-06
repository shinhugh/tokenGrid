/*
 * Refer to tokenGrid.h for descriptions.
 */

#include <stdlib.h>
#include <string.h>
#include "dynamicArray.h"
#include "dynamicString.h"
#include "tokenGrid.h"

#define FILE_BUFFER_SIZE 1024

// ------------------------------------------------------------

unsigned char TOKGD_OUT_OF_BOUNDS;

// ------------------------------------------------------------

tokenGrid * tokGd_tokenizeFile(FILE *file, const char *tokenSeparator,
const char *lineSeparator, unsigned char noEmptyToken) {

  unsigned int i, j;
  tokenGrid *result;
  dynamicArray *lines;
  char *newToken;
  unsigned int currIndex;
  unsigned int sepIndex;
  dynamicString str;
  char fileBuffer[FILE_BUFFER_SIZE];
  unsigned char sepMatch;

  TOKGD_OUT_OF_BOUNDS = 0;

  if(!file) {
    return 0;
  }

  result = malloc(sizeof(tokenGrid));
  result->tokens = malloc(sizeof(dynamicArray));
  result->totalCount = 0;
  lines = (dynamicArray*) result->tokens;
  dyArr_initialize(lines);
  dyArr_appendElement(lines, malloc(sizeof(dynamicArray)));
  dyArr_initialize(dyArr_getElement(lines, dyArr_getCount(lines) - 1));
  currIndex = 0;
  dyStr_initialize(&str);

  while(fgets(fileBuffer, FILE_BUFFER_SIZE, file)) {
    dyStr_appendStr(&str, fileBuffer);
    while(dyStr_getStr(&str)[currIndex]) {
      sepMatch = 0;
      if(dyStr_getStr(&str)[currIndex] == lineSeparator[0]) {
        sepIndex = 0;
        while(dyStr_getStr(&str)[currIndex + sepIndex]
        == lineSeparator[sepIndex]) {
          if(lineSeparator[sepIndex + 1] == 0) {
            newToken = malloc(currIndex + 1);
            memcpy(newToken, dyStr_getStr(&str), currIndex);
            newToken[currIndex] = 0;
            dyArr_appendElement(
            dyArr_getElement(lines, dyArr_getCount(lines) - 1), newToken);
            dyArr_appendElement(lines, malloc(sizeof(dynamicArray)));
            dyArr_initialize(dyArr_getElement(lines,
            dyArr_getCount(lines) - 1));
            result->totalCount++;
            dyStr_removePart(&str, 0, currIndex + sepIndex + 1);
            sepMatch = 1;
            break;
          }
          sepIndex++;
        }
      }
      else if(dyStr_getStr(&str)[currIndex] == tokenSeparator[0]) {
        sepIndex = 0;
        while(dyStr_getStr(&str)[currIndex + sepIndex]
        == tokenSeparator[sepIndex]) {
          if(tokenSeparator[sepIndex + 1] == 0) {
            newToken = malloc(currIndex + 1);
            memcpy(newToken, dyStr_getStr(&str), currIndex);
            newToken[currIndex] = 0;
            dyArr_appendElement(
            dyArr_getElement(lines, dyArr_getCount(lines) - 1), newToken);
            result->totalCount++;
            dyStr_removePart(&str, 0, currIndex + sepIndex + 1);
            sepMatch = 1;
            break;
          }
          sepIndex++;
        }
      }
      if(sepMatch) {
        currIndex = 0;
      } else {
        currIndex++;
      }
    }
  }

  if(currIndex > 0) {
    newToken = malloc(currIndex + 1);
    memcpy(newToken, dyStr_getStr(&str), currIndex);
    newToken[currIndex] = 0;
    dyArr_appendElement(
    dyArr_getElement(lines, dyArr_getCount(lines) - 1), newToken);
    result->totalCount++;
  }

  dyStr_deinitialize(&str);

  if(dyArr_getCount(dyArr_getElement(lines, dyArr_getCount(lines) - 1)) == 0) {
    dyArr_deinitialize(dyArr_getElement(lines, dyArr_getCount(lines) - 1));
    free(dyArr_getElement(lines, dyArr_getCount(lines) - 1));
    dyArr_removeElement(lines, dyArr_getCount(lines) - 1);
  }

  if(noEmptyToken) {
    for(i = 0; i < dyArr_getCount(lines); i++) {
      for(j = 0; j < dyArr_getCount(dyArr_getElement(lines, i)); j++) {
        if(((char*) dyArr_getElement(dyArr_getElement(lines, i), j))[0] == 0) {
          free(dyArr_getElement(dyArr_getElement(lines, i), j));
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

tokenGrid * tokGd_tokenizeStr(const char *str, const char *tokenSeparator,
const char *lineSeparator, unsigned char noEmptyToken) {

  unsigned int i, j;
  tokenGrid *result;
  dynamicArray *lines;
  char *newToken;
  unsigned int startIndex, currIndex;
  unsigned int sepIndex;

  TOKGD_OUT_OF_BOUNDS = 0;

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
      sepIndex = 0;
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
      sepIndex = 0;
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
          free(dyArr_getElement(dyArr_getElement(lines, i), j));
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

  TOKGD_OUT_OF_BOUNDS = 0;

  lines = (dynamicArray*) grid->tokens;

  if(lineIndex >= dyArr_getCount(lines)) {
    TOKGD_OUT_OF_BOUNDS = 1;
    return 0;
  }
  if(inlineIndex >= dyArr_getCount(dyArr_getElement(lines, lineIndex))) {
    TOKGD_OUT_OF_BOUNDS = 1;
    return 0;
  }

  return dyArr_getElement(dyArr_getElement(lines, lineIndex), inlineIndex);

}

// ------------------------------------------------------------

const char * tokGd_getToken_index(const tokenGrid *grid, unsigned int index) {

  unsigned int i;
  dynamicArray *lines;
  unsigned int currIndex, currLineLength;

  TOKGD_OUT_OF_BOUNDS = 0;

  lines = (dynamicArray*) grid->tokens;

  if(index >= grid->totalCount) {
    TOKGD_OUT_OF_BOUNDS = 1;
    return 0;
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

  TOKGD_OUT_OF_BOUNDS = 0;

  return grid->totalCount;

}

// ------------------------------------------------------------

unsigned int tokGd_getLineCount(const tokenGrid *grid) {

  dynamicArray *lines;

  TOKGD_OUT_OF_BOUNDS = 0;

  lines = (dynamicArray*) grid->tokens;

  return dyArr_getCount(lines);

}

// ------------------------------------------------------------

unsigned int tokGd_getLineTokenCount(const tokenGrid *grid,
unsigned int lineIndex) {

  dynamicArray *lines;

  TOKGD_OUT_OF_BOUNDS = 0;

  lines = (dynamicArray*) grid->tokens;

  if(lineIndex >= dyArr_getCount(lines)) {
    TOKGD_OUT_OF_BOUNDS = 1;
    return 0;
  }

  return dyArr_getCount(dyArr_getElement(lines, lineIndex));

}

// ------------------------------------------------------------

void tokGd_cleanup(tokenGrid *grid) {

  unsigned int i, j;
  dynamicArray *lines;

  TOKGD_OUT_OF_BOUNDS = 0;

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
