/**
 * @file virtualmachine.h
 * @author: Brecht Vandevoort
 *
 * @brief Definition of the virtual machine
 */
#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <stdint.h>

#define MEM_SIZE 32768
#define MEM_BYTE_SIZE (MEM_SIZE * 2)

/**
 * @brief Represents a virtual machine
 */
typedef struct
{
	uint16_t *memory;
	int instructionPointer;
} VirtualMachine;

/**
 * @brief Initializes a given virtual machine.
 * @param vm The virtual machine to initialize.
 */
void initVirtualMachine(VirtualMachine *vm);

/**
 * @brief Destroys a given virtual machine.
 * @param vm The virtual machine to destroy.
 */
void destroyVirtualMachine(VirtualMachine *vm);

#endif
