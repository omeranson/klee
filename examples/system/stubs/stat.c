#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <klee/klee.h>

int stat(const char *pathname, struct stat *buf) {
	strlen(pathname); // Verify path is readable till NUL terminator
	HAVOC(buf);
	return klee_range(-1, 1, __FUNCTION__);
}
