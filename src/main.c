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
	
	if(argc != 2)
	{
		fprintf(stderr, "No filename given.\n");
		return 1;
	}

	fprintf(stderr, "running...\n");
	
	initVirtualMachine(&vm);
	
	loadMemory(argv[1], &vm);
	
	state = runVirtualMachine(&vm);

	fprintf(stderr, "VM ended with state %d\n", state);

	destroyVirtualMachine(&vm);

	fprintf(stderr, "done!\n");
	return 0;
}
