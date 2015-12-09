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

#define REGISTER_INDEX(r) (VM_REGISTER_ADDRESS_MASK & r)
#define IS_VALID_REGISTER(r) ((VM_REGISTER_MASK & r) && REGISTER_INDEX(r) < VM_REGISTER_COUNT)
#define MAKE_VALID_VALUE(v) (v & VM_VALID_VALUE_MASK)

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
	uint16_t paramA, paramB, paramC;
	uint16_t value1, value2, value3;
  	uint32_t val32;
	int state = VM_STATE_RUNNING;
	
	opcode = nextMemoryElement(vm);

#ifdef DEBUG
	fprintf(stderr, "Executing opcode: %5d on address: %5d\n", opcode,vm->instructionPointer-1);
#endif

	switch(opcode)
	{
		case OP_HALT:
			state = VM_STATE_HALTED;
			break;
		case OP_SET:
			paramA = nextMemoryElement(vm);
			paramB = nextMemoryElement(vm);
			value1 = getValue(paramB, vm);
			if(storeValue(value1, paramA, vm))
			{
				fprintf(stderr, "Invalid register address: %d\n", paramA);
				state = VM_STATE_ERROR;
			}
			break;
		case OP_PUSH:
			paramA = nextMemoryElement(vm);
			value1 = getValue(paramA, vm);
			pushStack(value1, vm->stack);
			break;
		case OP_POP:
			paramA = nextMemoryElement(vm);
			if(popStack(&value1, vm->stack))
			{
				fprintf(stderr, "Could not pop from empty stack\n");
				state = VM_STATE_ERROR;
			}
			else
			{
				if(storeValue(value1, paramA, vm))
				{
					fprintf(stderr, "Invalid register address: %d\n", paramA);
					state = VM_STATE_ERROR;
				}
			}
			break;
		case OP_EQ:
		case OP_GT:
			paramA = nextMemoryElement(vm);
			paramB = nextMemoryElement(vm);
			paramC = nextMemoryElement(vm);
			value1 = getValue(paramB, vm);
			value2 = getValue(paramC, vm);
			if((value1 == value2 && opcode == OP_EQ)
					|| (value1 > value2 && opcode == OP_GT))
				value3 = 1;
			else
				value3 = 0;
			if(storeValue(value3, paramA, vm))
			{
				fprintf(stderr, "Invalid register address: %d\n", paramA);
				state = VM_STATE_ERROR;
			}
			break;
		case OP_JMP:
			paramA = nextMemoryElement(vm);
			vm->instructionPointer = getValue(paramA, vm);
			break;
		case OP_JT:
		case OP_JF:
			paramA = nextMemoryElement(vm);
			paramB = nextMemoryElement(vm);
			value1 = getValue(paramA, vm);
			if ((value1 != 0 && opcode == OP_JT) 
					|| (value1 == 0 && opcode == OP_JF))
			{
				vm->instructionPointer = getValue(paramB, vm);
			}
			break;
		case OP_ADD:
			paramA = nextMemoryElement(vm);
			paramB = nextMemoryElement(vm);
			paramC = nextMemoryElement(vm);
			value1 = getValue(paramB, vm);
			value1 += getValue(paramC, vm);
			value1 = MAKE_VALID_VALUE(value1);
			if(storeValue(value1, paramA, vm))
			{
				fprintf(stderr, "Invalid register address: %d\n", paramA);
				state = VM_STATE_ERROR;
			}
			break;
		case OP_MULT:
			paramA = nextMemoryElement(vm);
			paramB = nextMemoryElement(vm);
			paramC = nextMemoryElement(vm);
			value1 = getValue(paramB, vm);
			value2 = getValue(paramC, vm);
			val32 = (uint32_t)value1 * (uint32_t)value2;
			val32 = MAKE_VALID_VALUE(val32);
			value3 = (uint16_t)val32;
			if(storeValue(value3, paramA, vm))
			{
				fprintf(stderr, "Invalid register address: %d\n", paramA);
				state = VM_STATE_ERROR;
			}
			break;
		case OP_MOD:
			paramA = nextMemoryElement(vm);
			paramB = nextMemoryElement(vm);
			paramC = nextMemoryElement(vm);
			value1 = getValue(paramB, vm);
			value2 = getValue(paramC, vm);
			value3 = value1 % value2;
			if(storeValue(value3, paramA, vm))
			{
				fprintf(stderr, "Invalid register address: %d\n", paramA);
				state = VM_STATE_ERROR;
			}
			break;
		case OP_AND:
		case OP_OR:
			paramA = nextMemoryElement(vm);
			paramB = nextMemoryElement(vm);
			paramC = nextMemoryElement(vm);
			value1 = getValue(paramB, vm);
			value2 = getValue(paramC, vm);
			value3 = (opcode == OP_AND)? value1 & value2 : value1 | value2;
			if(storeValue(value3, paramA, vm))
			{
				fprintf(stderr, "Invalid register address: %d\n", paramA);
				state = VM_STATE_ERROR;
			}
			break;
		case OP_NOT:
			paramA = nextMemoryElement(vm);
			paramB = nextMemoryElement(vm);
			value1 = ~getValue(paramB, vm);
			value1 = MAKE_VALID_VALUE(value1);
			if(storeValue(value1, paramA, vm))
			{
				fprintf(stderr, "Invalid register address: %d\n", paramA);
				state = VM_STATE_ERROR;
			}
			break;
		case OP_RMEM:
			paramA = nextMemoryElement(vm);
			paramB = nextMemoryElement(vm);
			value1 = getValue(paramB, vm);
			value2 = vm->memory[value1];
			if(storeValue(value2, paramA, vm))
			{
				fprintf(stderr, "Invalid register address: %d\n", paramA);
				state = VM_STATE_ERROR;
			}
			break;
		case OP_WMEM:
			paramA = nextMemoryElement(vm);
			paramB = nextMemoryElement(vm);
			value1 = getValue(paramA, vm);
			value2 = getValue(paramB, vm);
			vm->memory[value1] = value2;
			break;
		case OP_CALL:
			paramA = nextMemoryElement(vm);
			pushStack(vm->instructionPointer, vm->stack);
			vm->instructionPointer = getValue(paramA, vm);
			break;
		case OP_RET:
			if(popStack(&value1, vm->stack))
			{
				fprintf(stderr, "Empty stack while executing ret: halting\n");
				state = VM_STATE_HALTED;
			}
			else
			{
				vm->instructionPointer = value1;
			}
			break;
		case OP_OUT:
			paramA = nextMemoryElement(vm);
			fprintf(stdout, "%c", getValue(paramA, vm));
			break;
		case OP_IN:
			paramA = nextMemoryElement(vm);
			/* fprintf(stderr, "Some info: op: %3d addr: %5d mem: %5d %5d %5d\n", vm->memory[vm->instructionPointer], vm->instructionPointer, vm->memory[vm->instructionPointer+1], vm->memory[vm->instructionPointer+2], vm->memory[vm->instructionPointer+3]); */
			value1 = inputsreamGetChar(vm->inputstream);
			if(storeValue(value1, paramA, vm))
			{
				fprintf(stderr, "Invalid register address: %d\n", paramA);
				state = VM_STATE_ERROR;
			}
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



