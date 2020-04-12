/*
 * Refer to dynamicString.h for descriptions.
 */

#include <stdlib.h>
#include <string.h>
#include "dynamicString.h"

#define INITIAL_ALLOC_SIZE 32
#define EXPANSION_FACTOR 2

// ------------------------------------------------------------

unsigned char DYSTR_ALLOC_ERROR;

// ------------------------------------------------------------

const char * dyStr_getStr(dynamicString *str) {

  DYSTR_ALLOC_ERROR = 0;

  return str->string;

}

// ------------------------------------------------------------

void dyStr_setStr(dynamicString *str, const char *newStr) {

  unsigned int newStrLength;
  char *transferPtr;
  unsigned int newSize;

  DYSTR_ALLOC_ERROR = 0;

  newStrLength = 0;
  while(newStr[newStrLength]) {
    newStrLength++;
  }

  if(newStrLength + 1 > str->alloc_size) {
    newSize = INITIAL_ALLOC_SIZE;
    while(newSize < newStrLength + 1) {
      newSize *= EXPANSION_FACTOR;
    }
    transferPtr = realloc(str->string, newSize);
    if(!transferPtr) {
      DYSTR_ALLOC_ERROR = 1;
      return;
    }
    str->string = transferPtr;
    str->alloc_size = newSize;
  }

  memcpy(str->string, newStr, newStrLength);
  str->string[newStrLength] = 0;

  str->length = newStrLength;

}

// ------------------------------------------------------------

void dyStr_appendStr(dynamicString *str, const char *newStr) {

  unsigned int newStrLength;
  char *transferPtr;
  unsigned int newSize;

  DYSTR_ALLOC_ERROR = 0;

  newStrLength = 0;
  while(newStr[newStrLength]) {
    newStrLength++;
  }

  if(str->length + newStrLength + 1 > str->alloc_size) {
    newSize = INITIAL_ALLOC_SIZE;
    while(newSize < str->length + newStrLength + 1) {
      newSize *= EXPANSION_FACTOR;
    }
    transferPtr = realloc(str->string, newSize);
    if(!transferPtr) {
      DYSTR_ALLOC_ERROR = 1;
      return;
    }
    str->string = transferPtr;
    str->alloc_size = newSize;
  }

  memcpy(str->string + str->length, newStr, newStrLength);
  str->string[str->length + newStrLength] = 0;

  str->length += newStrLength;

}

// ------------------------------------------------------------

void dyStr_removePart(dynamicString *str, unsigned int startIndex,
unsigned int count) {

  unsigned int i;
  unsigned int transferCount;

  DYSTR_ALLOC_ERROR = 0;

  if(startIndex + count >= str->length) {
    if(startIndex < str->length) {
      str->string[startIndex] = 0;
      str->length = startIndex;
    }
  }
  else {
    transferCount = str->length - (startIndex + count);
    for(i = 0; i < transferCount; i++) {
      str->string[startIndex + i] = str->string[startIndex + count + i];
    }
    str->string[startIndex + transferCount] = 0;
    str->length -= count;
  }

}

// ------------------------------------------------------------

unsigned int dyStr_getLength(dynamicString *str) {

  return str->length;

}

// ------------------------------------------------------------

void dyStr_fit(dynamicString *str) {

  char *transferPtr;

  DYSTR_ALLOC_ERROR = 0;

  transferPtr = realloc(str->string, str->length + 1);
  if(!transferPtr) {
    DYSTR_ALLOC_ERROR = 1;
    return;
  }
  str->string = transferPtr;
  str->alloc_size = str->length + 1;

}

// ------------------------------------------------------------

void dyStr_initialize(dynamicString *str) {

  DYSTR_ALLOC_ERROR = 0;

  str->string = malloc(INITIAL_ALLOC_SIZE);
  if(!str->string) {
    DYSTR_ALLOC_ERROR = 1;
    return;
  }
  str->string[0] = 0;
  str->length = 0;
  str->alloc_size = INITIAL_ALLOC_SIZE;

}

// ------------------------------------------------------------

void dyStr_deinitialize(dynamicString *str) {

  DYSTR_ALLOC_ERROR = 0;

  free(str->string);

}
