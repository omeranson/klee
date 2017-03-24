#include <alloca.h>
#include <errno.h>
#include <string.h>

#include <klee/klee.h>

#include "stubs_helper_macros.h"

char * readpassphrase(const char *prompt, char *buf, size_t bufsiz, int flags) {
	strlen(prompt);
	HAVOC_SIZE(buf, bufsiz-1);
	buf[bufsiz-1] = '\0';
	int ret = klee_range(-1, 1, __FUNCTION__);
	if (ret == 0) {
		return buf;
	}
	errno = klee_int(__FUNCTION__);
	return NULL;
}
