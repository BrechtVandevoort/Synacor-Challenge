/**
 * @file inputstream.h
 * @author: Brecht Vandevoort
 *
 * @brief Definition of the input stream for the virtual machine
 */
#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <stdio.h>
#include <stdint.h>

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
void initInputstream(char *filename, Inputstream *inputstream);

/**
 * @brief Reads a character from the given inputstream.
 * @param inputstream The inputstream.
 * @return The character, or 0 of the inputstream is empty.
 */
uint16_t inputsreamGetChar(Inputstream *inputstream);

/**
 * Writes a character into the stream for reading by the vm.
 * @param c The character to write
 * @param inputstream The inputstream.
 */
void inputstreamWriteChar(char c, Inputstream *inputstream);

#endif
