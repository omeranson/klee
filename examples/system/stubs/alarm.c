
#include <klee/klee.h>

unsigned int alarm(unsigned int seconds) {
	return klee_int(__FUNCTION__);
}
