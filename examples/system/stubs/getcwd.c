#include <alloca.h>
#include <stdlib.h>
#include <string.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

char *getcwd(char *buf, size_t size) {
	if (!buf) {
		HAVOC_SIZE(buf, size);
		return buf;
	}
	char * _buf = malloc(size);
	klee_make_symbolic(_buf, size, __FUNCTION__);
	return _buf;
}
