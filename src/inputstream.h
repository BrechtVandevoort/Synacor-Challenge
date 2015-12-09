/**
 * @file inputstream.h
 * @author: Brecht Vandevoort
 *
 * @brief Definition of the input stream for the virtual machine
 */
#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <stdio.h>

#define INPUTSTREAM_BUFFER_SIZE 4096

typedef struct
{
	int pos;
	int size;
	char buffer[INPUTSTREAM_BUFFER_SIZE];
} Inputstream;

/**
 * @brief Initializes the inputstream
 * @param filename optional filename to load into the buffer. NULL if starting empty.
 * @param inputstream The inputstream.
 */
void initBuffer(char *filename, Inputstream *inputstream);

/**
 * @brief Reads a character from the given inputstream.
 * @param inputstream The inputstream.
 * @return The character.
 */
int inputsreamGetChar(Inputstream *inputstream);

#endif
