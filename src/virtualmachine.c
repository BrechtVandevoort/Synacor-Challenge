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
	vm->memory = (uint16_t *) malloc(MEM_BYTE_SIZE);
	vm->instructionPointer = 0;
}

void destroyVirtualMachine(VirtualMachine *vm)
{
	free(vm->memory);
}
