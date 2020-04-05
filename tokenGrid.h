/*
 * Translates a stream or string into a 2-D array of tokens.
 */

#ifndef TOKENGRID_H
#define TOKENGRID_H

#include <stdio.h>
#include "dynamicArray.h"

// ------------------------------------------------------------

// Type definitions

typedef struct tokenGrid {
  void * tokens;
  unsigned int totalCount;
} tokenGrid;

// ------------------------------------------------------------

// Functions

/*
 * Tokenizes a file stream into a 2-D array that represents the token layout in
 * the stream.
 * The token separator string marks the division between two tokens on the same
 * line.
 * A line separator string marks the division between two lines of tokens, hence
 * why the result is a 2-D array. Typically, LF or CRLF would be passed in for
 * this parameter.
 * tokGd_cleanup() should be called when grid usage is complete to avoid memory
 * leaks.
 * Return: A struct that holds the tokens in a 2-D array format
 */
tokenGrid * tokGd_tokenizeFile(FILE *file, const char *tokenSeparator,
const char *lineSeparator);

/*
 * Tokenizes a string into a 2-D array that represents the token layout in the
 * string.
 * The token separator string marks the division between two tokens on the same
 * line.
 * A line separator string marks the division between two lines of tokens, hence
 * why the result is a 2-D array. Typically, LF or CRLF would be passed in for
 * this parameter.
 * tokGd_cleanup() should be called when grid usage is complete to avoid memory
 * leaks.
 * Return: A struct that holds the tokens in a 2-D array format
 */
tokenGrid * tokGd_tokenizeStr(const char *str, const char *tokenSeparator,
const char *lineSeparator);

/*
 * Get a token from the result of a tokenize call by its coordinates in the
 * grid.
 */
const char * tokGd_getToken_coor(const tokenGrid *grid, unsigned int lineIndex,
unsigned int inlineIndex);

/*
 * Get a token from the result of a tokenize call by its overall index amongst
 * all tokens in the grid.
 */
const char * tokGd_getToken_index(const tokenGrid *grid, unsigned int index);

/*
 * Get the total number of tokens tokenized.
 * Return: Total number of tokens in grid
 */
unsigned int tokGd_getTotalCount(const tokenGrid *grid);

/*
 * Get the number of token lines.
 * Return: Number of token lines
 */
unsigned int tokGd_getLineCount(const tokenGrid *grid);

/*
 * Get the number of tokens in a specific line.
 * Return: Number of tokens in a specific line
 */
unsigned int tokGd_getLineTokenCount(const tokenGrid *grid,
unsigned int lineIndex);

/*
 * Free memory allocated for a token grid.
 * Must be called after every tokenize call to avoid memory leaks.
 */
void tokGd_cleanup(tokenGrid *grid);

// ------------------------------------------------------------

#endif
