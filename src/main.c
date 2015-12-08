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
	int i;
	
	if(argc != 2)
	{
		fprintf(stderr, "No filename given.\n");
		return 1;
	}

	fprintf(stderr, "running...\n");
	
	initVirtualMachine(&vm);
	
	loadMemory(argv[1], &vm);
	
	for (i = 0; i < 10; ++i)
		fprintf(stdout, "The next instruction is: %d\n", nextMemoryElement(&vm));

	destroyVirtualMachine(&vm);

	fprintf(stderr, "done!\n");
	return 0;
}
