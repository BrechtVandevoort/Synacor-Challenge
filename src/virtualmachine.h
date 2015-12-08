/**
 * @file virtualmachine.h
 * @author: Brecht Vandevoort
 *
 * @brief Definition of the virtual machine
 */
#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <stdint.h>

#include "opcodes.h"

#define VM_MEM_ELEM_COUNT 32768
#define VM_MEM_ELEM_SIZE 2
#define VM_MEM_SIZE (VM_MEM_ELEM_COUNT * VM_MEM_ELEM_SIZE)

#define VM_STATE_RUNNING 0
#define VM_STATE_HALTED 1
#define VM_STATE_ERROR 2

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

/**
 * @brief Executes a single step in the virtual machine
 * @param vm The virtual machine
 * @return The state the virtual machine is in after executing
 */
int executeStep(VirtualMachine *vm);

/**
 * @brief Executes the virtual machine, until the vm halts or encounters an error.
 * @param vm The virtual machine to run.
 * @return The state of the virtual machine after executing.
 */
int runVirtualMachine(VirtualMachine *vm);

#endif
