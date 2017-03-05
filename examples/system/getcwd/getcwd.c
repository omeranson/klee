#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char cwd[PATH_MAX];

int main(int argc, char * argv[]) {
	printf("cwd is here: %p\n", cwd);
	getcwd(cwd, PATH_MAX);
	if (strcmp(cwd, "/") == 0) {
		printf("I'm at root!\n");
		printf("cwd is: %s\n", cwd);
		assert(0 && "I'm at root!\n");
		return 0;
	}
	if (strncmp(cwd, "/home", sizeof("/home")-1) == 0) {
		printf("I'm at home!\n");
		printf("cwd is: %s\n", cwd);
		assert(0 && "I'm at home!\n");
		return 0;
	}
	if (strncmp(cwd, "/tmp", sizeof("/tmp")-1) == 0) {
		printf("I'm fleeting!\n");
		printf("cwd is: %s\n", cwd);
		assert(0 && "I'm fleeting!\n");
		return 0;
	}
	printf("I'm... somewhere else!\n");
	printf("cwd is: %s\n", cwd);
	assert(0 && "I'm... somewhere else!\n");
	/*
	int len = strlen(cwd);
	for (int idx = 0; idx < len; idx++) {
		char c = cwd[idx];
		if ((c >= 32) && (c <= 127)) {
			printf("%c", c);
		} else {
			printf("%02x", c);
		}
	}
	write(1, "\n", sizeof("\n")-1); */
	return 0;
}

