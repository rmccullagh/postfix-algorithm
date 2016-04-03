/*
*  Copyright (c) 2016 Ryan McCullagh <me@ryanmccullagh.com>
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
