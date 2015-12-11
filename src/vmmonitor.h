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
 * @brief Writes the monitor on the screen
 * @param showVMInfo If nonzero, the VM info will be written.
 * @param showOutput If nonzero, the outputsstream will be written.
 * @param vm The virtual machine.
 */
void vmmonitorWriteMonitor(int showVMInfo, int showOutput, VirtualMachine *vm);

/**
 * @brief Monitor the run of a virtual machine.
 * This function runs the vm until a given number of opcodes are executed
 * or until the vm changes it's state.
 * @param numSteps The number of opcodes the vm needs to execute
 * @param vm The virtual machine.
 * @return the return value of the virtual machine
 */
int vmmonitorRunSteps(int numSteps, VirtualMachine *vm);

/**
 * @brief Starts a monitored run of the virtual machine
 * @param vm the virtual machine
 * @return the return value of the virtual machine
 */
int vmmonitorStart(VirtualMachine *vm);

#endif
