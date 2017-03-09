#include <sys/socket.h>

#include <klee/klee.h>

int socket(int domain, int type, int protocol) {
	int retval = klee_int(__FUNCTION__);
	// We assume sockets are limited to 1024, because of the code in select
	klee_assume((retval <= 1024) || (retval == -1));
	return retval;
}
