#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <klee/klee.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
