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

#include <object.h>
#include <stdlib.h>

#include "calc.h"

Stack pstack = {0};
static GC_List gclist;

void gcinit(void)
{
	gclist.node_count = 0;
	gclist.list = NULL;
}

void gcterm(void)
{
	GC_Node *head = gclist.list;

	while(head != NULL) {
		GC_Node *next = head->next;	
	
		objectDestroy((Object *)head->value);
	
		free(head);

		head = next;
	}
}

void gccollect(void)
{
	GC_Node *head = gclist.list;

	while(head != NULL) {
		GC_Node *next = head->next;	
	
		if(head->refcount == 0 && head->value != NULL) {	
			objectDestroy((Object *)head->value);
		}

		head = next;
	}
}


void stackinit(void)
{
	size_t i;
	for(i = 0; i < STACK_SIZE; ++i) {
		pstack.table[i] = NULL;	
	}	
	
	pstack.stackp = 0;
	pstack.stacksize = 0;
}

int stackpush(Object *value)
{
	if(pstack.stackp >= 0 && pstack.stackp < STACK_SIZE) {
		pstack.table[pstack.stackp++] = value;
		pstack.stacksize += 1;
		return 0;
	} else {
		return 1;
	}
}

extern void gcrefdec(void *value)
{
	GC_Node *node;
	if(gcsearch((void *)value, (void **)&node) == 0) {
		if(node->refcount > 0)
			node->refcount -= 1;	
	}
}

Object *stackpop(void)
{
	if(pstack.stackp > 0 && pstack.stackp - 1 < STACK_SIZE) {
		Object *value = pstack.table[--pstack.stackp];
		pstack.stacksize -= 1;
		gctouch(value);

		GC_Node *node;
		if(gcsearch((void *)value, (void **)&node) == 0) {
			node->refcount += 1;	
		}

		return value;
	} else {
		return NULL;	
	}
}

extern int gcsearch(void *value, void **out)
{
	GC_Node *head = gclist.list;
	*out = NULL;
	int retval = 1;

	while(head != NULL) {
				
		if(head->value == value) {
			*out = head;
			retval = 0;
			break;
		}

		head = head->next;
	}

	return retval;
}

void gctouch(void *value)
{
	if(gclist.list == NULL) {
		GC_Node *node =  malloc(sizeof(GC_Node));
		node->value = value;
		node->refcount = 0;
		node->next = NULL;
		gclist.list = node;
		gclist.node_count = 1;	
	} else {
		GC_Node *out;
		if(gcsearch((void *)value, (void **)&out) == 0) {
			out->refcount += 1;
		} else {
			GC_Node *newnode = malloc(sizeof(GC_Node));
			newnode->value = value;
			newnode->refcount = 0;
			newnode->next = gclist.list;
			gclist.list = newnode;	
			gclist.node_count += 1;		
		}	
	}
}



