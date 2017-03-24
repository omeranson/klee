#include <errno.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */

#include <klee/klee.h>

int setuid(uid_t uid) {
	errno = klee_int(__FUNCTION__);
	return klee_range(-1, 1, __FUNCTION__);
}
