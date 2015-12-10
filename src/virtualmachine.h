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
#include "stack.h"
#include "inputstream.h"
#include "outputstream.h"

#define VM_MEM_ELEM_COUNT 32768
#define VM_MEM_ELEM_SIZE 2
#define VM_MEM_SIZE (VM_MEM_ELEM_COUNT * VM_MEM_ELEM_SIZE)

#define VM_REGISTER_COUNT 8
#define VM_REGISTER_MASK 0x8000
#define VM_REGISTER_ADDRESS_MASK 0x7fff

#define VM_VALID_VALUE_MASK 0x7fff

#define VM_STATE_RUNNING 0
#define VM_STATE_HALTED 1
#define VM_STATE_ERROR 2

/**
 * @brief Macro for checking if the given register address r is valid.
 */
#define IS_VALID_REGISTER(r) ((VM_REGISTER_MASK & (r)) && REGISTER_INDEX(r) < VM_REGISTER_COUNT)

/**
 * @brief Macro for converting a register address to a 0-based index number.
 */ 
#define REGISTER_INDEX(r) (VM_REGISTER_ADDRESS_MASK & (r))

/**
 * @brief Represents a virtual machine
 */
typedef struct
{
	uint16_t memory[VM_MEM_ELEM_COUNT];
	uint16_t registers[VM_REGISTER_COUNT];
	Stack *stack;
	uint16_t instructionPointer;
	int instructionCount;
	Inputstream *inputstream;
	Outputstream *outputstream;
} VirtualMachine;

/**
 * @brief Initializes a given virtual machine.
 * @param inputstreamFile Name of the inputstream file, or NULL if not used
 * @param vm The virtual machine to initialize.
 */
void initVirtualMachine(char *inputstreamFile, FILE *ostream,  VirtualMachine *vm);

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

/**
 * @brief Translates the given memory element into a value.
 * If the memory element is the address of a register,
 * the value of this register is returned.
 * If not, the value itself is returned.
 * @param memElem The memory element to translate to a value.
 * @return The translated value.
 */
uint16_t getValue(uint16_t memElem, VirtualMachine *vm);


/**
 * @brief Stores a value in a register.
 * @param value The value to store.
 * @param registerAddress Address of the register.
 * @param vm The virtual machine.
 * @return 0 on success, -1 if the register is invalid.
 */
int storeValue(uint16_t value, uint16_t registerAddress, VirtualMachine *vm);

/**
 * @brief Loads params based on the opcode
 * @param params Array to load the params into
 * @param opcode The opcode to load params for
 * @param vm The virtual machine
 */
void loadParams(uint16_t *params, uint16_t opcode, VirtualMachine *vm);

#endif
