/**
 * @file vmmonitor.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of the vm monitor for monitoring the execution of a vm.
 */
#include "vmmonitor.h"

#include "memmanager.h"

void vmmonitorWriteVMInfo(FILE *stream, VirtualMachine *vm)
{
	int i;

	/* Print current position */
	fprintf(stream, "POSITION: %d\n", vm->instructionPointer);

	/* Print register values */
#ifdef MONITOR_VERBOSE
	fprintf(stream, "REGISTERS:\n");
#endif
	for(i = 0; i < VM_REGISTER_COUNT; ++i)
		fprintf(stream, "R%d: %5d ", i, vm->registers[i]);
	fprintf(stream, "\n");

#ifdef MONITOR_VERBOSE
	/* Print memory near the current position of the instruction pointer */
	fprintf(stream, "NEAR MEMORY INFO:\n");
	for(i = vm->instructionPointer-10; i < vm->instructionPointer + 20; ++i)
		vmmonitorWriteMemoryLine(stream, i, vm);
#endif
}

void vmmonitorWriteMemoryLine(FILE *stream, uint16_t address, VirtualMachine *vm)
{
	uint16_t value;
   
	/* Check if valid address */
	if(address < 0 || address >= VM_MEM_ELEM_COUNT)
		return;

	value = vm->memory[address];

	/* Write indicator if on current instruction */
	if(address == vm->instructionPointer)
		fprintf(stream, "->");
	else
		fprintf(stream, "  ");

	/* write address and value, without interpretation */
	fprintf(stream, "[%05d] %5d: ", address, value);

	/*write opcode if valid*/
	if(value < OPCODE_NUM_OPS)
		fprintf(stream, "%6s ", opcodeGetName(value));
	else
		fprintf(stream, "       ");

	/* write register if valid */
	if(IS_VALID_REGISTER(value))
		fprintf(stream, "R%d ", REGISTER_INDEX(value));
	else
		fprintf(stream, "   ");

	/* Write ascii char if valid */
	if(value >= 32 && value <= 126)
		fprintf(stream, "\"%c\"n", (char)value);
	else
		fprintf(stream, "\n");
}

int monitorVirtualMachine(int breakpoint, VirtualMachine *vm)
{
	int  state;
	int count = 0;

	fprintf(stderr, "breakpoint placed at %d instructions\n", breakpoint);
	do
	{
		fprintf(stderr, "Instruction %d\n", count);
		if(count++ == breakpoint)
		{
			storeVMState("vmstate.bin", vm);
			fprintf(stderr, "Breakpoint detected, waiting for input\n");
			fflush(stdin);
			getchar();
			fflush(stdin);
			fprintf(stderr, "resuming\n");
			loadVMState("vmstate.bin", vm);
		}
		vmmonitorWriteVMInfo(stderr, vm);
		state = executeStep(vm);
	} while(state == VM_STATE_RUNNING);

	return state;
}
