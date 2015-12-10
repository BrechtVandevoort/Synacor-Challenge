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

int storeMemory(char *filename, VirtualMachine *vm)
{
	/* TODO */
	(void)(filename);
	(void)(vm);
	return -1;
}

int storeVMState(char *filename, VirtualMachine *vm)
{
	FILE *f;
	f = fopen(filename, "wb");
	if(f == NULL)
	{
		fprintf(stderr, "Failed to write state to file.\n");
		return -1;
	}

	/* Write pointer */
	if (fwrite(&vm->instructionPointer, sizeof(uint16_t), 1, f) != 1)
	{
		fprintf(stderr, "Failed to write instructionpointer to file\n");
		fclose(f);
		return -1;
	}

	/* Write registers */
	if (fwrite(vm->registers, sizeof(uint16_t), VM_REGISTER_COUNT, f) != VM_REGISTER_COUNT)
	{
		fprintf(stderr, "Failed to write registers to file\n");
		fclose(f);
		return -1;
	}


	/* TODO: memory */
	fclose(f);

	return 0;
}

int loadVMState(char *filename, VirtualMachine *vm)
{
	FILE *f;
	f = fopen(filename, "rb");
	if(f == NULL)
	{
		fprintf(stderr, "Failed to read state from file.\n");
		return -1;
	}

	/* read pointer */
	if (fread(&vm->instructionPointer, sizeof(uint16_t), 1, f) != 1)
	{
		fprintf(stderr, "Failed to read instructionpointer from file\n");
		fclose(f);
		return -1;
	}

	/* Write registers */
	if (fread(vm->registers, sizeof(uint16_t), VM_REGISTER_COUNT, f) != VM_REGISTER_COUNT)
	{
		fprintf(stderr, "Failed to read registers from file\n");
		fclose(f);
		return -1;
	}

	/* TODO: memory */
	fclose(f);

	return 0;
}

