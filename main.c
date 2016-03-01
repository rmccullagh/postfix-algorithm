#include <stdio.h>
#include <unistd.h>
#include <object.h>
#include <stddef.h>
#include <linkedlist.h>

#include "calc.h"
#include "calcio.h"
#include "calcoperator.h"
#include "calcbuffer.h"

extern Stack pstack;

static void dtor(void *value)
{
	objectDestroy((Object *)value);
}

static void opdtor(void *value)
{

}

static void addhandler(void)
{

}

typedef struct binaryop {
	unsigned char op;
	void(*handler)(void);
} binaryop;

#define IS_DIGIT(c) ((((c) >= '0') && ((c) <= '9')))

#define IS_OPERATOR(c) ((((c) == '+') || ((c) == '-')))


#define IS_WHITE(c) ((((c) == '\t') || ((c) == ' ')))

int main(void)
{
	gcinit();
	stackinit();

	while(1) {
		char buffer[80];
		ssize_t bytes_read = raw_input("calc> ", buffer, sizeof(buffer));
		if(bytes_read == EOF) {
			return 0;
		} else {	
			
			Buffer p;
			buffer_init(&p, buffer, bytes_read);
			size_t i = 0;
			while(p.pos != p.end) {
				if(IS_DIGIT(*p.pos)) {
					int num = *p.pos - '0';
					stackpush(newLong(num));
					printf("PUSH %d\n", num);
				} else if(IS_OPERATOR(*p.pos)) {
					if(pstack.stacksize < 2) {
						fprintf(stderr,
							"operator '%c' takes 2 args\n", *p.pos);
						goto finally;

					} else {
						Object* op2 = stackpop();
						Object* op1 = stackpop();
							
						if(*p.pos == '+') {
							printf("POP %ld\n", O_LVAL(op2));
							printf("POP %ld\n", O_LVAL(op1));
							long result;
							result = O_LVAL(op1) + O_LVAL(op2);

							Object *retval = newLong(result);
							printf("ADD\n");
							stackpush(retval);
							printf("PUSH %ld\n", result);
						} else if(*p.pos == '-') {
							long result;
							result = O_LVAL(op1) - O_LVAL(op2);

							Object *retval = newLong(result);
							stackpush(retval);	
						}

					}	
					
				} 
				else if (IS_WHITE(*p.pos)) 
				{
					goto out;
				}
				else 
				{
					fprintf(stderr, "Invalid token %c\n", *p.pos);
					goto finally;
				}

				out:
					p.pos++;
					i++;
			}

			if(pstack.stacksize == 1) {
				Object *top = stackpop();
				objectEcho(top);
			} else {
				printf("To many values: %zu", pstack.stacksize);
			}
			

			finally:
				gcterm();
				gcinit();
				stackinit();
				printf("\n");
		}
	}

	return 0;
}

