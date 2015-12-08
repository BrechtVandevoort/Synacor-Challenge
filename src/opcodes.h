/**
 * @file opcodes.h
 * @author Brecht Vandevoort
 *
 * @brief Definition of the different opcodes.
 */

#ifndef OPCODES_H
#define OPCODES_H

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

#endif
