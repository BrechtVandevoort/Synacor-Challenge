/**
 * @file main.c
 * @author: Brecht Vandevoort
 * 
 * @brief Main function.
 */
#include <stdio.h>

#include "virtualmachine.h"

int main(int argc, char *argv[]) {
	VirtualMachine vm;
	
	fprintf(stderr, "running...\n");
	
	initVirtualMachine(&vm);
	
	destroyVirtualMachine(&vm);

	fprintf(stderr, "done!\n");
	return 0;
}
