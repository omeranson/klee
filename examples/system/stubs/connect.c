#include <sys/types.h>
#include <sys/socket.h>

#include <klee/klee.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	int retval = klee_int(__FUNCTION__);
	// TODO Set errno?
	klee_assume((retval == 0) || (retval == -1));
	return retval;
}
