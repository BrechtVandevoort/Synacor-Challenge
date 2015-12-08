/**
 * @file virtualmachine.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of the virtual machine.
 */
#include "virtualmachine.h"

#include <stdio.h>
#include <stdlib.h>

void initVirtualMachine(VirtualMachine *vm)
{
	vm->memory = (uint16_t *) malloc(VM_MEM_SIZE);
	vm->instructionPointer = 0;
}

void destroyVirtualMachine(VirtualMachine *vm)
{
	free(vm->memory);
}

uint16_t nextMemoryElement(VirtualMachine *vm)
{
	return vm->memory[vm->instructionPointer++];
}

int executeStep(VirtualMachine *vm)
{
	uint16_t opcode = nextMemoryElement(vm);

	switch(opcode)
	{
		case OP_HALT:
			return VM_STATE_HALTED;
			break;
		case OP_OUT:
			fprintf(stdout, "%c", nextMemoryElement(vm));
			return VM_STATE_RUNNING;
			break;
		case OP_NOOP:
			return VM_STATE_RUNNING;
			break;
		default:
			fprintf(stderr, "Unrecognized opcode: %d\n", opcode);
			return VM_STATE_ERROR;
			break;
	}
}

int runVirtualMachine(VirtualMachine *vm)
{
	int  state;

	do
	{
		state = executeStep(vm);
	} while(state == VM_STATE_RUNNING);

	return state;
}
