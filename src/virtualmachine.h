/**
 * @file virtualmachine.h
 * @author: Brecht Vandevoort
 *
 * @brief Definition of the virtual machine
 */
#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <stdint.h>

#define VM_MEM_ELEM_COUNT 32768
#define VM_MEM_ELEM_SIZE 2
#define VM_MEM_SIZE (VM_MEM_ELEM_COUNT * VM_MEM_ELEM_SIZE)

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

/**
 * @brief Returns the next element from memory, based on the instructionPointer.
 * @return The next element from memory.
 */
uint16_t nextMemoryElement(VirtualMachine *vm);

#endif
