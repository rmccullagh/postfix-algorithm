#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calcio.h"

ssize_t raw_input(const char* prompt, char* buffer, size_t buffer_size)
{
	size_t i = 0;
	int c;
	memset(buffer, '\0', buffer_size);
	printf("%s", prompt);
	
	while((c = getchar()) != EOF) {
		if(i < buffer_size - 1) {
			if((char)c == '\n') {
				break;
			} else {
				buffer[i++] = (char)c;
			}
		} else {
			int cc;
			while((cc = getchar()) != EOF && cc != '\n');
			break;
		}
	}

	buffer[i] = '\0';

	if(c == EOF) {
		return EOF;
	}
	
	return i;
}

