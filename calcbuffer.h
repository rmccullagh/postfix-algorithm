#ifndef CALC_BUFFER_H
#define CALC_BUFFER_H

#include <stddef.h>

typedef struct Buffer {
	const unsigned char *buffer;
	const unsigned char *begin;
	const unsigned char *end;
	const unsigned char *pos;
} Buffer;

extern void buffer_init(Buffer* p, const char *rbuffer, size_t rbufferlen);

#endif
