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

#ifndef CALC_H
#define CALC_H

/* 2^16
 *
 * Object is size 16 bytes per so max 2^16 / sizeof(Object)
 */

#define STACK_SIZE 65535

typedef struct GC_Node {
	void *value;
	unsigned int refcount;
	struct GC_Node *next;
} GC_Node;

typedef struct GC_List {
	size_t   node_count;
	GC_Node *list;	
} GC_List;

extern void gccollect(void);

extern void gcinit(void);
extern void gctouch(void *);
extern int  gcsearch(void *, void **);
extern void gcrefdec(void *);
extern void gcterm(void);


typedef struct Stack {
	size_t  stackp;
	size_t  stacksize;
	Object *table[STACK_SIZE];
} Stack;

extern void stackinit(void);


extern int stackpush(Object *);
extern Object *stackpop(void);


#endif
