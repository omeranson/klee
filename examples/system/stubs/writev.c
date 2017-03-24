#include <alloca.h>
#include <errno.h>
#include <string.h>
#include <sys/uio.h>

#include <klee/klee.h>

ssize_t writev(int fd, const struct iovec *iov, int iovcnt) {
	ssize_t total = 0;
	int idx;
	for (idx = 0; idx < iovcnt; idx++) {
		total += iov[idx].iov_len;
	}
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, total+1, __FUNCTION__);
}
