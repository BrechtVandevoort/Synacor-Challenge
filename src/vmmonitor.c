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
	for(i = vm->instructionPointer-2; i < vm->instructionPointer + 9; ++i)
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

void vmmonitorWriteOperation(FILE *stream, uint16_t address, VirtualMachine *vm)
{
	int i;
	uint16_t opcode, value;

	if(address < 0 || address >= VM_MEM_ELEM_COUNT)
		return;

	/* Write address */
	fprintf(stream, "[%5d] ", address);
	
	opcode = vm->memory[address];
	if(opcode < OPCODE_NUM_OPS)
	{
		/* Write opcode */
		fprintf(stream, "%4s ", opcodeGetName(opcode));
		/* Write params */
		for(i = 1; i <= OPCODE_MAX_PARAMS; ++i)
		{
			if(i <= opcodeParamCount[opcode])
			{
				value = vm->memory[address + i];
				if(IS_VALID_REGISTER(value))
					fprintf(stream, "R%d       ", REGISTER_INDEX(value));
				else
				{
					if(value >= 32 && value <= 126)
						fprintf(stream, "%5d(%c) ", value, (char) value);
					else
						fprintf(stream, "%5d    ", value);
				}
			}
			else
			{
				fprintf(stream, "         ");
			}
		}
		fprintf(stream, "\t");
		/* Write registers */
		for(i = 0; i < VM_REGISTER_COUNT; ++i)
			fprintf(stream, "<R%d:%5d> ", i, vm->registers[i]);
	}
	else
	{
		/* Write invalid opcode as data */
		fprintf(stream, "DATA: %d", opcode);
	}

	fprintf(stream, "\n");
}

void vmmonitorWriteMonitor(int showVMInfo, int showOutput, VirtualMachine *vm)
{
	if(showVMInfo)
	{
		SET_CURSOR_POS(stdout,0,0);
		vmmonitorWriteVMInfo(stdout, vm);
	}
	if(showOutput)
	{
		SET_CURSOR_POS(stdout,0,VMMONITOR_VM_STATE_LINES);
		vmmonitorWriteVMOutputstream(stdout, vm);
	}
}

int vmmonitorRunSteps(int numSteps, int breakpoint, FILE *opStream, VirtualMachine *vm)
{
	int  state = VM_STATE_RUNNING;
	int count = 0;

	while (state == VM_STATE_RUNNING && count < numSteps && vm->instructionPointer != breakpoint)
	{
		if(opStream)
			vmmonitorWriteOperation(opStream, vm->instructionPointer, vm);
		state = executeStep(vm);
		count++;
	}

	return state;
}

int vmmonitorStart(VirtualMachine *vm)
{
	int state = VM_STATE_RUNNING;
	int steps;
	int writeOperations = 0;
	int breakpoint = -1;
	FILE *f;

	f = fopen("vmrun.out", "w");

	/* Clear console before running */
	system("clear");

	do
	{
		vmmonitorWriteMonitor(1,1,vm);
		steps = vmmonitorReadInput(&writeOperations, &breakpoint, vm);
		if(writeOperations)
			state = vmmonitorRunSteps(steps, breakpoint, f, vm);
		else
			state = vmmonitorRunSteps(steps, breakpoint, NULL, vm);
	} while(state == VM_STATE_RUNNING || state == VM_STATE_WAITING_FOR_INPUT);

	fclose(f);

	return state;
}

int vmmonitorReadInput(int *writeOperations, int *breakpoint, VirtualMachine *vm)
{
	int c;
	int numSteps = 0;
	int reg, address, value;

	/* Clear part of console for input */
	SET_CURSOR_POS(stdout, 0, VMMONITOR_VM_STATE_LINES + VMMONITOR_VM_OUTPUT_LINES);
	fprintf(stdout, "                                                           \n");
	SET_CURSOR_POS(stdout, 0, VMMONITOR_VM_STATE_LINES + VMMONITOR_VM_OUTPUT_LINES);

	fprintf(stdout, "INPUT: ");
	c = getchar();

	/* Next instruction */
	if (c == '\n')
		numSteps = 1;
	
	/* Write to input stream */
	else if(c == '>')
	{
		do
		{
			c = getchar();
			inputstreamWriteChar(c, vm->inputstream);
		} while(c != '\n');
	}

	/* Run multiple steps */
	else if(c == ':')
		scanf("%d", &numSteps);

	/* Jump to address */
	else if(c == 'j')
	{
		if(scanf("%d", &address))
			vm->instructionPointer = address;
	}

	/* Set register */
	else if(c == 'r')
	{
		if(scanf("%d %d", &reg, &value))
			vm->registers[reg] = value;
	}

	/* Change writing operations to file */
	else if(c == 'w')
		*writeOperations = 1 - *writeOperations;
	

	/* Dump merory */
	else if(c == 'm')
		vmmonitorDumpMemory(vm);

	/* dump output to file */
	else if(c == 'o')
		vmmonitorDumpOutput(vm);

	/* Set breakpoint */
	else if(c == 'b')
		scanf("%d", breakpoint);

	/* Flush input */
	while (c != '\n' && c != EOF) c = getchar();

	return numSteps;
}


void vmmonitorDumpMemory(VirtualMachine *vm)
{
	int i = 0;
	int opcode;
	FILE *f;

	f = fopen("memdump.out", "w");

	while(i < VM_MEM_ELEM_COUNT)
	{
		opcode = vm->memory[i];
		vmmonitorWriteOperation(f, i, vm);
		if(opcode < OPCODE_NUM_OPS)
			i += opcodeParamCount[opcode];
		++i;
	}

	fclose(f);
}

void vmmonitorDumpOutput(VirtualMachine *vm)
{
	FILE *f;

	f = fopen("outputdump.out", "w");
	fputs(vm->outputstream->buffer, f);
	fclose(f);
}
