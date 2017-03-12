#include <sys/types.h>
#include <sys/socket.h>

#include <klee/klee.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	// TODO Set errno?
	return klee_range(-1, 1, __FUNCTION__);
}
