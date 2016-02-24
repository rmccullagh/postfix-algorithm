#include "calcbuffer.h"

void buffer_init(Buffer* p, const char *rbuffer, size_t rbufferlen)
{
	const unsigned char *buffer = (const unsigned char *)rbuffer;

	p->buffer = buffer;
	p->begin = p->buffer + 0;
	p->end = p->buffer + rbufferlen;
	p->pos = p->buffer + 0;
}
