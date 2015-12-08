/**
 * @file virtualmachine.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of the virtual machine.
 */
#include "virtualmachine.h"

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
