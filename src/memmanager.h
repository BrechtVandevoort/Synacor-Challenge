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

/**
 * @brief Stores the date of the given vm  into the given file.
 * @param filename Name of the file to store into.
 * @param vm The virtual machine to store data from.
 * @return The number of bytes stored, or -1 if failed.
 */
int storeMemory(char *filename, VirtualMachine *vm);

/**
 * @brief Stores the current state of the vm into the given file.
 * @param filename The name of the file.
 * @param vm The virtual machine
 * @return 0 success, -1 if failed.
 */
int storeVMState(char *filename, VirtualMachine *vm);

/**
 * @brief Loads the current state of the vm from the given file.
 * @param filename The name of the file.
 * @param vm The virtual machine
 * @return 0 success, -1 if failed.
 */
int loadVMState(char *filename, VirtualMachine *vm);

#endif
