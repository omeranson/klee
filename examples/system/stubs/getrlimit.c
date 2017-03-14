#include <alloca.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

int getrlimit(int resource, struct rlimit *rlim) {
	HAVOC(rlim);
	return klee_range(-1, 1, __FUNCTION__);
}
