/**
 * @file main.c
 * @author: Brecht Vandevoort
 * 
 * @brief Main function.
 */
#include <stdio.h>

#include "virtualmachine.h"
#include "memmanager.h"

int main(int argc, char *argv[]) {
	VirtualMachine vm;
	int state;
	char *inputstreamFile = NULL;

	if(argc < 2)
	{
		fprintf(stderr, "Usage: ./synacor filename.bin [stdinputfile]\n");
		return 1;
	}

	if(argc >= 3)
	{
		inputstreamFile = argv[2];
	}

	fprintf(stderr, "running...\n");
	
	initVirtualMachine(inputstreamFile, &vm);
	
	loadMemory(argv[1], &vm);
	
	state = runVirtualMachine(&vm);

	fprintf(stderr, "VM ended with state %d\n", state);

	destroyVirtualMachine(&vm);

	fprintf(stderr, "done!\n");
	return 0;
}
