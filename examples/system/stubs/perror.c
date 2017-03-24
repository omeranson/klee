#include <errno.h>
#include <stdio.h>
#include <string.h>

void perror(const char *s) {
	//printf("%s: %s", s, strerror(errno));
}

