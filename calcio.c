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

