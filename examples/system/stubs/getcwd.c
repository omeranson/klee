#include <alloca.h>
#include <stdlib.h>
#include <string.h>

#include <klee/klee.h>

char *getcwd(char *buf, size_t size) {
	if (!buf) {
		char * _buf = malloc(size);
		klee_make_symbolic(_buf, sizeof(_buf), "getcwd");
		return _buf;
	} else {
		char * temp = alloca(size);
		klee_make_symbolic(temp, size, "getcwd");
		memcpy(buf, temp, size);
		return buf;
	}
}
