#include <alloca.h>
#include <string.h>
#include <sys/uio.h>

#include <klee/klee.h>

ssize_t writev(int fd, const struct iovec *iov, int iovcnt) {
	ssize_t total = 0;
	int idx;
	for (idx = 0; idx < iovcnt; idx++) {
		total += iov[idx].iov_len;
	}
	if ((fd == 1) || (fd == 2)) {
		//char * buffer = (char*)alloca(total+1);
		//char * p = buffer;
		//for (idx = 0; idx < iovcnt; idx++) {
		//	memcpy(p, iov[idx].iov_base, iov[idx].iov_len);
		//	p += iov[idx].iov_len;
		//}
		//p[0] = '\0';
		//klee_warning(buffer);
	}
	// TODO Set errno?
	return klee_range(-1, total+1, __FUNCTION__);
}
