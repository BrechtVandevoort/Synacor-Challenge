/**
 * @file opcodes.c
 * @author: Brecht Vandevoort
 *
 * @brief Implementation of functionality related to the different opcodes.
 */
#include "opcodes.h"

int opcodeParamCount[] = 
{
	0, /* OP_HALT */
	2, /* OP_SET */
	1, /* OP_PUSH */
	1, /* OP_POP */
	3, /* OP_EQ */
	3, /* OP_GT */
	1, /* OP_JMP */
	2, /* OP_JT */
	2, /* OP_JF */
	3, /* OP_ADD */
	3, /* OP_MULT */
	3, /* OP_MOD */
	3, /* OP_AND */
	3, /* OP_OR */
	2, /* OP_NOT */
	2, /* OP_RMEM */
	2, /* OP_WMEM */
	1, /* OP_CALL */
	0, /* OP_RET */
	1, /* OP_OUT */
	1, /* OP_IN */
	0  /* OP_NOOP */
};

char *opcodeNames[] = 
{
	"halt",
	"set",
	"push",
	"pop",
	"eq",
	"gt",
	"jmp",
	"jt",
	"jf",
	"add",
	"mult",
	"mod",
	"and",
	"or",
	"not",
	"rmem",
	"wmem",
	"call",
	"ret",
	"out",
	"in",
	"noop",
	"INVALID"
};

char* opcodeGetName(uint16_t opcode)
{
	if(opcode < OPCODE_NUM_OPS)
		return opcodeNames[opcode];
	else
		return opcodeNames[OPCODE_NUM_OPS];
}
