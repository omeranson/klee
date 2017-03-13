#include <time.h>

time_t time(time_t *t) {
	time_t result;
	klee_make_symbolic(&result, sizeof(result), __FUNCTION__);
	if (t) {
		*t = result;
	}
	return result;
}
