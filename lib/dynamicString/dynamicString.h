/*
 * A runtime flexible string.
 */

#ifndef DYNAMICSTRING_H
#define DYNAMICSTRING_H

// ------------------------------------------------------------

// Global flags
// Flags are all reset at the start of every function call.

extern unsigned char DYSTR_ALLOC_ERROR;

// ------------------------------------------------------------

// Type definitions

typedef struct dynamicString {
  char *string;
  unsigned int length;
  unsigned int alloc_size;
} dynamicString;

// ------------------------------------------------------------

// Functions

/*
 * Get the string.
 * String is read-only; make copy for unrestricted use.
 * Return: Address of first char of string
 */
const char * dyStr_getStr(dynamicString *str);

/*
 * Replace the string entirely.
 * The source string must be null-terminated.
 */
void dyStr_setStr(dynamicString *str, const char *newStr);

/*
 * Append a string.
 * The source string must be null-terminated.
 */
void dyStr_appendStr(dynamicString *str, const char *newStr);

/*
 * Remove a part of a string, shifting down all following chars to fill the gap.
 * Out-of-bounds is okay; only the part that is relevant to the string will be
 * removed.
 */
void dyStr_removePart(dynamicString *str, unsigned int startIndex,
unsigned int count);

/*
 * Get length.
 * Return: Length of string
 */
unsigned int dyStr_getLength(dynamicString *str);

/*
 * Reallocate memory so that there is no unused memory for the string.
 * Make a tight fit.
 * Not wise to call if chars will be added in the future, as it will have to
 * expand again anyways, adding runtime overhead.
 */
void dyStr_fit(dynamicString *str);

/*
 * Prepare for usage.
 * Must be called before usage.
 * Must be followed by a deinitialize call once usage is complete to avoid
 * memory leaks.
 */
void dyStr_initialize(dynamicString *str);

/*
 * Free any memory allocated in the instance's lifetime.
 * Do not use the instance after calling this function.
 * Must be called to avoid a memory leak.
 */
void dyStr_deinitialize(dynamicString *str);

// ------------------------------------------------------------

#endif
