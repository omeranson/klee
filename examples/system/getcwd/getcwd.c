#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
	char cwd[PATH_MAX];
	cwd[10] = '/';
	getcwd(cwd, 10);
	assert(cwd[10] == '/');
	if (strcmp(cwd, "") == 0) {
		printf("I'm not anywhere...\n");
		assert(0 && "I'm not anywhere...\n");
		return 0;
	}
	if (cwd[0] != '/') {
		printf("I'm relative!\n");
		assert(0 && "I'm relative!\n");
		return 0;
	}
	if (strcmp(cwd, "/") == 0) {
		printf("I'm at root!\n");
		assert(0 && "I'm at root!\n");
		return 0;
	}
	if (strncmp(cwd, "/home", sizeof("/home")-1) == 0) {
		printf("I'm at home!\n");
		assert(0 && "I'm at home!\n");
		return 0;
	}
	if (strncmp(cwd, "/tmp", sizeof("/tmp")-1) == 0) {
		printf("I'm fleeting!\n");
		assert(0 && "I'm fleeting!\n");
		return 0;
	}
	printf("I'm... somewhere else!\n");
	assert(0 && "I'm... somewhere else!\n");
	return 0;
}

