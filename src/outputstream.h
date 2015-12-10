/**
 * @file outputstream.h
 * @author: Brecht Vandevoort
 *
 * @brief Definition of the outputstream for the virtual machine.
 */
#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H

#include <stdio.h>

#define OUTPUTSTREAM_BUFFER_SIZE 1048576

typedef struct
{
	char buffer[OUTPUTSTREAM_BUFFER_SIZE];
	int bufferSize;
	FILE *stream;
} Outputstream;


/**
 * @brief Initializes the output stream.
 * @param stream An optional stream to write output to. NULL if not used.
 * @param outputstream The outputstream.
 */
void initOutputstream(FILE *stream, Outputstream *outputstream);

/**
 * @brief Writes a character to the output stream.
 * @param c The character to write
 * @param outputstream The outputstream.
 */
void outputstreamWriteChar(char c, Outputstream *outputstream);

#endif
