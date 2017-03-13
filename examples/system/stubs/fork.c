#include <stdlib.h>
#include <unistd.h>

pid_t fork(void) {
	klee_warning("fork is not allowed");
	abort();
}
