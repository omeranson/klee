#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <klee/klee.h>

int setsockopt(int sockfd, int level, int optname,
	      const void *optval, socklen_t optlen) {
	return klee_range(-1, 1, __FUNCTION__);
}

