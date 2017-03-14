// XXX Should model uname, but this is easier
#include <alloca.h>
#include <string.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int gethostname(char *name, size_t len) {
	HAVOC_SIZE(name, len);
	return klee_range(-1, 1, __FUNCTION__);
}
