#include <alloca.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <klee/klee.h>

ssize_t write(int fd, const void *buf, size_t count) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, count+1, __FUNCTION__);
}
