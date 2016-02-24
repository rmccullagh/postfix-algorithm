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
