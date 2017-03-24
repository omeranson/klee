#include <alloca.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

ssize_t readlink(const char *pathname, char *buf, size_t bufsiz) {
	strlen(pathname);
	HAVOC_SIZE(buf, bufsiz);
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, bufsiz, __FUNCTION__);
}
