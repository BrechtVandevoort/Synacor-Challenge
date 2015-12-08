/**
 * @file memmanager.h
 * @author: Brecht Vandevoort
 *
 * @brief Definition of the memory manager for loading the memory of the virtual machine from file.
 */

#ifndef MEMMANAGER_H
#define MEMMANAGER_H

#include "virtualmachine.h"

/**
 * @brief Loads the data of the given file into the virtual machine.
 * @param filename Name of the file to load.
 * @param vm The virtual machine to load the data into.
 * @return the number of bytes loaded into memory, or -1 if failed.
 */
int loadMemory(char *filename, VirtualMachine *vm);

#endif
