/**
 * @file memmanager.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of the memory manager for loading the memory of the virtual machine from file.
 */

#include "memmanager.h"

#include <stdio.h>

int loadMemory(char *filename, VirtualMachine *vm)
{
	FILE *f;
	size_t result;

	f = fopen(filename, "rb");
	if(f == NULL)
	{
		fprintf(stderr, "Failed to load memory\n");
		return -1;
	}

	result = fread(vm->memory, VM_MEM_ELEM_SIZE, VM_MEM_ELEM_COUNT, f);
	
	fclose(f);

	return result;
}
