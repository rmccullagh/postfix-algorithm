#ifndef CALC_OPERATOR_H
#define CALC_OPERATOR_H

typedef void(*opmethod)(unsigned int operandcount);

#define ASSOC_RIGHT 1
#define ASSOC_LEFT 2

typedef enum OP_CODE {
	OP_POW, OP_MUL, OP_DIV, OP_ADD, OP_SUB
} OP_CODE;

typedef struct OpCodeHandler {
	OP_CODE   op_code;
	unsigned int op_precedence;
	unsigned int op_associativity;
} OpCodeHandler;

struct OpCodeHandler operatortable[] = {
	{ OP_POW, 4, ASSOC_RIGHT },
	{ OP_MUL, 3, ASSOC_LEFT },
	{ OP_DIV, 3, ASSOC_LEFT },
	{ OP_ADD, 2, ASSOC_LEFT },
	{ OP_SUB, 2, ASSOC_LEFT }
};

#endif
