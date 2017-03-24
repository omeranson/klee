#include <alloca.h>
#include <errno.h>
#include <string.h>
#include <sys/uio.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

ssize_t readv(int fd, const struct iovec *iov, int iovcnt) {
	int idx;
	ssize_t total = 0;
	for (idx = 0; idx < iovcnt; idx++) {
		HAVOC_SIZE(iov[idx].iov_base, iov[idx].iov_len);
		total += iov[idx].iov_len;
	}
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, total+1, __FUNCTION__);
}
