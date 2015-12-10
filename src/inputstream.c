/**
 * @file inputstream.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of the inputstream virtual machine.
 */
#include "inputstream.h"

void initInputstream(char *filename, Inputstream *inputstream)
{
	FILE *f;

	inputstream->pos = 0;
	inputstream->size = 0;
	f = fopen(filename, "rb");
	if(f == NULL)
	{
		fprintf(stderr, "Failed to load inputstream\n");
		return;
	}

	inputstream->size = fread(inputstream->buffer, sizeof(char), INPUTSTREAM_BUFFER_SIZE, f);

	fclose(f);
}

uint16_t inputsreamGetChar(Inputstream *inputstream)
{
	int result;

	if(inputstream->size > 0) {
		result = inputstream->buffer[inputstream->pos++];
		inputstream->pos %= INPUTSTREAM_BUFFER_SIZE;
		inputstream->size--;
		return result;
	}
	
	return 0;
}

void inputstreamWriteChar(char c, Inputstream *inputstream)
{
	int writePos;

	if(inputstream->size == INPUTSTREAM_BUFFER_SIZE)
	{
		fprintf(stderr, "Buffer overflow in inputstream.\n");
		return;
	}

	writePos = (inputstream->pos + inputstream->size) % INPUTSTREAM_BUFFER_SIZE;
	inputstream->buffer[writePos] = c;
	inputstream->size++;
}

