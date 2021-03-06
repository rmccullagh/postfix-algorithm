/*
 * Copyright (c) 2016 Ryan McCullagh <me@ryanmccullagh.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
