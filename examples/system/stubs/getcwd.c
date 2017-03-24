#include <alloca.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

char *getcwd(char *buf, size_t size) {
	if (!buf) {
		buf = malloc(size);
	}
	HAVOC_SIZE(buf, size-1);
	buf[size-1] = '\0';
	errno = klee_int(__FUNCTION__); // TODO Return NULL?
	return buf;
}
