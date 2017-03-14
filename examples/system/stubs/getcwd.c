#include <alloca.h>
#include <stdlib.h>
#include <string.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

char *getcwd(char *buf, size_t size) {
	klee_warning("getcwd stub");
	if (!buf) {
		buf = malloc(size);
	}
	HAVOC_SIZE(buf, size-1);
	buf[size-1] = '\0';
	return buf;
}
