#include <stdlib.h>
#include <sys/mman.h>

#include <klee/klee.h>

void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset) {
	void * result = malloc(length);
	klee_make_symbolic(result, length, __FUNCTION__);
	return result;
}
