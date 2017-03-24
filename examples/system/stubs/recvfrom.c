#include <alloca.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
		struct sockaddr *src_addr, socklen_t *addrlen) {
	HAVOC_SIZE(buf, len);
	if (src_addr) {
		void * temp = alloca(1024);
		klee_make_symbolic(temp, 1024, __FUNCTION__);
		memcpy(src_addr, temp, *addrlen);
		if (*addrlen > 1024) {
			klee_warning("recvfrom: *addrlen can be very big");
		}
		*addrlen = klee_int(__FUNCTION__);
	}
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, len+1, __FUNCTION__);
}
