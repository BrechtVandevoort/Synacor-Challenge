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

int inputsreamGetChar(Inputstream *inputstream)
{
	int result;

	while(inputstream->pos < inputstream->size) {
		result = inputstream->buffer[inputstream->pos++];
		/* if(result != '\n') */
			return result;
	}
	
	return getchar();
}
