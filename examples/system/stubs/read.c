#include <alloca.h>
#include <string.h>
#include <unistd.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

ssize_t read(int fd, void *buf, size_t count) {
	HAVOC_SIZE(buf, count);
	// TODO Set errno?
	return klee_range(-1, count+1, __FUNCTION__);
}
