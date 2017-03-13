
#include <klee/klee.h>

unsigned int sleep(unsigned int seconds) {
	return klee_range(0, seconds, __FUNCTION__);
}
