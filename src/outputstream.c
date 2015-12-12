/**
 * @file outputstream.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of the outputstream for the virtual machine.
 */
#include "outputstream.h"

#include <string.h>

void initOutputstream(FILE *stream, Outputstream *outputstream)
{
	memset(outputstream->buffer, 0, OUTPUTSTREAM_BUFFER_SIZE * sizeof(char));
	outputstream->bufferSize = 0;
	outputstream->stream = stream;
}

void outputstreamWriteChar(char c, Outputstream *outputstream)
{
	int pos = outputstream->bufferSize;

	if(pos < OUTPUTSTREAM_BUFFER_SIZE)
	{
		outputstream->buffer[pos] = c;
		outputstream->bufferSize++;
	}

	if(outputstream->stream)
		fprintf(outputstream->stream, "%c", c);
}
