#include <assert.h>
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

int getrandom(void *buf, size_t buflen, unsigned int flags) {
	return syscall(SYS_getrandom, buf, buflen, flags, 0,0,0,0,0,0);
}

int t1() {
	int r;
	int read = getrandom(&r, sizeof(r), 0);
	if (read < 0) {
		printf("Error!\n");
		return 1;
	}
	if (read < sizeof(r)) {
		printf("Didn't read enough random data\n");
		return 1;
	}
	assert(r != 3);
	printf("Didn't get 3!\n");
	return 0;
}

int t2() {
	int r;
	int read = getrandom(&r, 2*sizeof(r), 0);
	if (read < 0) {
		printf("Error!\n");
		return 1;
	}
	if (read < sizeof(r)) {
		printf("Didn't read enough random data\n");
		return 1;
	}
	assert(r != 3);
	printf("Didn't get 3!\n");
	return 0;
}

int main(int argc, char * argv[]) {
	t1();
	t2();
	return 0;
}
