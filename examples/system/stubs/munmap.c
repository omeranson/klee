#include <stdlib.h>
#include <sys/mman.h>

#include <klee/klee.h>

int munmap(void *addr, size_t length) {
	int choice = klee_choose(2);
	if (!choice) {
		return -1;
	}
	free(addr); // XXX I think this may be technically wrong
	return 0;
}
