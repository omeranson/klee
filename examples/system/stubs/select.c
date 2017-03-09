#include <alloca.h>
#include <string.h>
#include <sys/select.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		struct timeval *timeout) {
	if (readfds) {
		HAVOC(readfds);
	}
	if (writefds) {
		HAVOC(writefds);
	}
	if (exceptfds) {
		HAVOC(exceptfds);
	}
	int retval = klee_int(__FUNCTION__);
	klee_assume(retval <= nfds);
	klee_assume(retval >= -1);
	return retval;
}
