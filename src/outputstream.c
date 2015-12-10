/**
 * @file outputstream.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of the outputstream for the virtual machine.
 */
#include "outputstream.h"


void initOutputstream(FILE *stream, Outputstream *outputstream)
{
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
