#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <klee/klee.h>

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags) {
	struct iovec *iov = msg->msg_iov;
	size_t iovcnt = msg->msg_iovlen;

	ssize_t total = 0;
	int idx;
	for (idx = 0; idx < iovcnt; idx++) {
		total += iov[idx].iov_len;
	}
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, total+1, __FUNCTION__);
}

