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

