#include <alloca.h>
#include <string.h>
#include <unistd.h>

#include <klee/klee.h>

ssize_t write(int fd, const void *buf, size_t count) {
	if ((fd == 1) || (fd == 2)) {
		char * buffer = (char*)alloca(count+1);
		memcpy(buffer, buf, count);
		buffer[count] = '\0';
		klee_warning(buffer);
	}
	int retval = klee_int(__FUNCTION__);
	// TODO Set errno?
	klee_assume((retval <= count) || (retval == -1));
	return retval;
}
