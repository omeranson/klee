#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int main(int argc, char * argv[]) {
	char cwd[PATH_MAX];
	getcwd(cwd, PATH_MAX);
	if (strcmp(cwd, "/") == 0) {
		write(1, "I'm at root!\n", sizeof("I'm at root!\n")-1);
		return 0;
	}
	if (strncmp(cwd, "/home", sizeof("/home")-1) == 0) {
		write(1, "I'm at home!\n", sizeof("I'm at home!\n")-1);
		return 0;
	}
	if (strncmp(cwd, "/tmp", sizeof("/tmp")-1) == 0) {
		write(1, "I'm fleeting!\n", sizeof("I'm fleeting!\n")-1);
		return 0;
	}
	write(1, "I'm... somewhere else!\n", sizeof("I'm... somewhere else!\n")-1);
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

