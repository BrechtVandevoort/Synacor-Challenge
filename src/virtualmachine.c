/**
 * @file virtualmachine.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of the virtual machine.
 */
#include "virtualmachine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Macro for converting a register address to a 0-based index number.
 */ 
#define REGISTER_INDEX(r) (VM_REGISTER_ADDRESS_MASK & (r))

/**
 * @brief Macro for checking if the given register address r is valid.
 */
#define IS_VALID_REGISTER(r) ((VM_REGISTER_MASK & (r)) && REGISTER_INDEX(r) < VM_REGISTER_COUNT)

/**
 * @brief Macro for converting a given value v into a valid value. 
 * result = v % 32768.
 */
#define MAKE_VALID_VALUE(v) ((v) & VM_VALID_VALUE_MASK)

/**
 * @brief Macro used in function executeStep().
 *  It stores the given value into a register based on the first param.
 * This macro will check for a possible failure and write an error message.
 */
#define SAFE_STORE_MACRO(value) \
	do { \
		if(storeValue(value, params[0], vm)) \
		{ \
			fprintf(stderr, "Invalid register address: %d\n", params[0]); \
			state = VM_STATE_ERROR; \
		} \
	} while(0)


void initVirtualMachine(char *inputstreamFile, VirtualMachine *vm)
{
	vm->instructionPointer = 0;
	memset(vm->memory, 0, VM_MEM_SIZE);
	memset(vm->registers, 0, VM_REGISTER_COUNT * sizeof(uint16_t));
	vm->stack = (Stack*) malloc(sizeof(Stack));
	initStack(vm->stack);
	vm->inputstream = (Inputstream*) malloc(sizeof(Inputstream));
	initBuffer(inputstreamFile, vm->inputstream);
}

void destroyVirtualMachine(VirtualMachine *vm)
{
	memset(vm->memory, 0, VM_MEM_SIZE);
	destroyStack(vm->stack);
	free(vm->stack);
}

uint16_t nextMemoryElement(VirtualMachine *vm)
{
	return vm->memory[vm->instructionPointer++];
}

int executeStep(VirtualMachine *vm)
{
	uint16_t opcode;
	uint16_t params[OPCODE_MAX_PARAMS];
	uint16_t value1, value2, value3;
  	uint32_t val32;
	int state = VM_STATE_RUNNING;
	
	opcode = nextMemoryElement(vm);

	loadParams(params, opcode, vm);

#ifdef DEBUG
	fprintf(stderr, "Executing opcode: %5d on address: %5d\n", opcode,vm->instructionPointer-1);
#endif

	switch(opcode)
	{
		case OP_HALT:
			state = VM_STATE_HALTED;
			break;
		case OP_SET:
			value1 = getValue(params[1], vm);
			SAFE_STORE_MACRO(value1);
			break;
		case OP_PUSH:
			value1 = getValue(params[0], vm);
			pushStack(value1, vm->stack);
			break;
		case OP_POP:
			if(popStack(&value1, vm->stack))
			{
				fprintf(stderr, "Could not pop from empty stack\n");
				state = VM_STATE_ERROR;
			}
			else
				SAFE_STORE_MACRO(value1);
			break;
		case OP_EQ:
		case OP_GT:
			value1 = getValue(params[1], vm);
			value2 = getValue(params[2], vm);
			if((value1 == value2 && opcode == OP_EQ)
					|| (value1 > value2 && opcode == OP_GT))
				value3 = 1;
			else
				value3 = 0;
			SAFE_STORE_MACRO(value3);
			break;
		case OP_JMP:
			vm->instructionPointer = getValue(params[0], vm);
			break;
		case OP_JT:
			value1 = getValue(params[0], vm);
			if(value1 != 0)
				vm->instructionPointer = getValue(params[1], vm);
			break;
		case OP_JF:
			value1 = getValue(params[0], vm);
			if(value1 == 0)
				vm->instructionPointer = getValue(params[1], vm);
			break;
		case OP_ADD:
			value1 = getValue(params[1], vm);
			value1 += getValue(params[2], vm);
			value1 = MAKE_VALID_VALUE(value1);
			SAFE_STORE_MACRO(value1);
			break;
		case OP_MULT:
			value1 = getValue(params[1], vm);
			value2 = getValue(params[2], vm);
			val32 = (uint32_t)value1 * (uint32_t)value2;
			val32 = MAKE_VALID_VALUE(val32);
			value3 = (uint16_t)val32;
			SAFE_STORE_MACRO(value3);
			break;
		case OP_MOD:
			value1 = getValue(params[1], vm);
			value2 = getValue(params[2], vm);
			value3 = value1 % value2;
			SAFE_STORE_MACRO(value3);
			break;
		case OP_AND:
		case OP_OR:
			value1 = getValue(params[1], vm);
			value2 = getValue(params[2], vm);
			value3 = (opcode == OP_AND)? value1 & value2 : value1 | value2;
			SAFE_STORE_MACRO(value3);
			break;
		case OP_NOT:
			value1 = ~getValue(params[1], vm);
			value1 = MAKE_VALID_VALUE(value1);
			SAFE_STORE_MACRO(value1);
			break;
		case OP_RMEM:
			value1 = getValue(params[1], vm);
			value2 = vm->memory[value1];
			SAFE_STORE_MACRO(value2);
			break;
		case OP_WMEM:
			value1 = getValue(params[0], vm);
			value2 = getValue(params[1], vm);
			vm->memory[value1] = value2;
			break;
		case OP_CALL:
			pushStack(vm->instructionPointer, vm->stack);
			vm->instructionPointer = getValue(params[0], vm);
			break;
		case OP_RET:
			if(popStack(&value1, vm->stack))
			{
				fprintf(stderr, "Empty stack while executing ret: halting\n");
				state = VM_STATE_HALTED;
			}
			else
				vm->instructionPointer = value1;
			break;
		case OP_OUT:
			fprintf(stdout, "%c", getValue(params[0], vm));
			break;
		case OP_IN:
			value1 = inputsreamGetChar(vm->inputstream);
			SAFE_STORE_MACRO(value1);
			break;
		case OP_NOOP:
			break;
		default:
			fprintf(stderr, "Unrecognized opcode: %d\n", opcode);
			state = VM_STATE_ERROR;
			break;
	}

	if(state == VM_STATE_ERROR)
		fprintf(stderr, "Error while executing operation %d on address %d\n", opcode, vm->instructionPointer-1);

	return state;
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

uint16_t getValue(uint16_t memElem, VirtualMachine *vm)
{
	if(IS_VALID_REGISTER(memElem))
	{
		return vm->registers[REGISTER_INDEX(memElem)];
	}

	return memElem;
}

int storeValue(uint16_t value, uint16_t registerAddress, VirtualMachine *vm)
{
	if(!IS_VALID_REGISTER(registerAddress))
		return -1;

	vm->registers[REGISTER_INDEX(registerAddress)] = value;

	return 0;
}

void loadParams(uint16_t *params, uint16_t opcode, VirtualMachine *vm)
{
	int i;
	int numParams = opcodeParamCount[opcode];

	for(i = 0; i < numParams; ++i)
	{
		params[i] = nextMemoryElement(vm);
	}
}

