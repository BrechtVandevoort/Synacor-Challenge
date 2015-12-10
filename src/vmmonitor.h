/**
 * @file vmmonitor.h
 * @author: Brecht Vandevoort
 *
 * @brief Definition of the vm monitor for monitoring the execution of a vm.
 */
#ifndef VMMONITOR_H
#define VMMONITOR_H

#include <stdio.h>
#include <stdlib.h>

#include "virtualmachine.h"

#define VMMONITOR_VM_STATE_LINES 22
#define VMMONITOR_VM_OUTPUT_LINES 10

/**
 * @brief Writes the state of the virtual machine to a given stream.
 * @param stream The stream to write to.
 * @param vm The virtual machine.
 */
void vmmonitorWriteVMInfo(FILE *stream, VirtualMachine *vm);

/**
 * @brief Writes the last lines of the virtual machine's outputstream to a given stream.
 * @param stream The stream to write to.
 * @param mvm The virtual machine.
 */
void vmmonitorWriteVMOutputstream(FILE *stream, VirtualMachine *vm);

/**
 * @brief Writes a line to represent te value of a memory element
 * @param stream The stream to write to.
 * @param address The address of the value.
 * @param vm The virtual machine
 */
void vmmonitorWriteMemoryLine(FILE *stream, uint16_t address, VirtualMachine *vm);

/**
 * @brief Monitor the run of a virtual machine.
 * @param vm The virtual machine.
 * @return the return value of the virtual machine
 */
int monitorVirtualMachine(VirtualMachine *vm);

#endif
