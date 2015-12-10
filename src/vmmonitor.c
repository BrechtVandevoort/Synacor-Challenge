/**
 * @file vmmonitor.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of the vm monitor for monitoring the execution of a vm.
 */
#include "vmmonitor.h"

#include "memmanager.h"

#define SET_CURSOR_POS(stream,x,y) fprintf(stream, "\033[%d;%dH", (y)+1, (x)+1)

void vmmonitorWriteVMInfo(FILE *stream, VirtualMachine *vm)
{
	int i;

	/* Print counter and current position */
	fprintf(stream, "OPCODE COUNTER: %7d    POSITION: %d\n\n", vm->instructionCount, vm->instructionPointer);

	/* Print register values */
	fprintf(stream, "REGISTERS: ");
	for(i = 0; i < VM_REGISTER_COUNT; ++i)
	fprintf(stream, "<R%d: %5d> ", i, vm->registers[i]);
	fprintf(stream, "\n\n");

	/* Print memory near the current position of the instruction pointer */
	fprintf(stream, "NEAR MEMORY INFO:\n");
	for(i = vm->instructionPointer-5; i < vm->instructionPointer + 10; ++i)
		vmmonitorWriteMemoryLine(stream, i, vm);

	/* Print horizontal line */
	fprintf(stream, "                                        \n--------------------------------------\n");
}

void vmmonitorWriteVMOutputstream(FILE *stream, VirtualMachine *vm)
{
	int pos;
	int count = 0;

	pos = vm->outputstream->bufferSize - 1;
	while(pos >= 0 && count < 15) {
		if(vm->outputstream->buffer[pos] == '\n')
			count++;
		pos--;
	}
	pos++;
	while(pos < vm->outputstream->bufferSize) {
		if(vm->outputstream->buffer[pos] == '\n')
			fprintf(stream, "                                                                             ");
		fprintf(stream, "%c", vm->outputstream->buffer[pos]);
		pos++;
	}

	fprintf(stream, "                                                               \n");
	fprintf(stream, "                                                               \n");
	fprintf(stream, "                                                               \n");
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
		fprintf(stream, "%4s ", opcodeGetName(value));
	else
		fprintf(stream, "       ");

	/* write register if valid */
	if(IS_VALID_REGISTER(value))
		fprintf(stream, "R%d ", REGISTER_INDEX(value));
	else
		fprintf(stream, "   ");

	/* Write ascii char if valid */
	if(value >= 32 && value <= 126)
		fprintf(stream, "\"%c\"          \n", (char)value);
	else
		fprintf(stream, "              \n");
}

int monitorVirtualMachine(VirtualMachine *vm)
{
	int  state;
	system("clear");

	do
	{
		SET_CURSOR_POS(stdout,0,0);
		vmmonitorWriteVMInfo(stdout, vm);
		vmmonitorWriteVMOutputstream(stdout, vm);
		state = executeStep(vm);
	} while(state == VM_STATE_RUNNING);

	return state;
}
