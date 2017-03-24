#include <errno.h>
#include <string.h>

#include <klee/klee.h>

long long
strtonum(const char *nptr, long long minval, long long maxval,
		const char **errstr) {
	strlen(nptr);
	long long result;
	klee_make_symbolic(&result, sizeof(result), __FUNCTION__);
	if ((result > maxval) || (result < minval)) {
		if (errstr) {
			*errstr = "Error in strtonum";
		}
		errno = klee_int(__FUNCTION__);
		return 0;
	}
	if (errstr) {
		*errstr = 0;
	}
	return result;
}

uint32_t arc4random(void) { 
	uint32_t result;
	klee_make_symbolic(&result, sizeof(result), __FUNCTION__);
	return result;
}

