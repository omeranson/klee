#include <alloca.h>
#include <string.h>
#include <sys/timex.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int adjtimex(struct timex *buf) {
	HAVOC(buf);
	// int retval = klee_int("adjtimex retval");
	return 0; // TODO Error code?
}
