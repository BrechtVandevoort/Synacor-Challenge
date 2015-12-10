/**
 * @file opcodes.h
 * @author Brecht Vandevoort
 *
 * @brief Definition of the different opcodes.
 */
#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

#define OP_HALT	0
#define OP_SET 1
#define OP_PUSH	2
#define OP_POP 3
#define OP_EQ 4
#define OP_GT 5
#define OP_JMP 6
#define OP_JT 7
#define OP_JF 8
#define OP_ADD 9
#define OP_MULT 10
#define OP_MOD 11
#define OP_AND 12
#define OP_OR 13
#define OP_NOT 14
#define OP_RMEM 15
#define OP_WMEM 16
#define OP_CALL 17
#define OP_RET 18
#define OP_OUT 19
#define OP_IN 20
#define OP_NOOP 21
#define OPCODE_NUM_OPS 22

#define OPCODE_MAX_PARAMS 3

/**
 * @brief Lookup table for the number of params for each opcode
 */
extern int opcodeParamCount[];

/**
 * @brief Lookup table for the name of each opcode
 */
extern char *opcodeName[];

/**
 * @brief Returns a pointer to the name of the given opcode
 * @param opcode The opcode.
 * @return A pointer to the name of the given opcode.
 */
char *opcodeGetName(uint16_t opcode);

#endif
