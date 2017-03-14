#include <alloca.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
	if (addr) {
		if (*addrlen > 1024) {
			klee_warning("recvfrom: *addrlen can be very big");
		}
		HAVOC_SIZE(addr, *addrlen);
		*addrlen = klee_int(__FUNCTION__);
	}
	// TODO Set errno?
	return klee_range(-1, 1024, __FUNCTION__);
}
