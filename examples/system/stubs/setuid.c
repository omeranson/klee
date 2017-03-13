#include <unistd.h>
#include <sys/types.h>          /* See NOTES */

#include <klee/klee.h>

int setuid(uid_t uid) {
	return klee_range(-1, 1, __FUNCTION__);
}
