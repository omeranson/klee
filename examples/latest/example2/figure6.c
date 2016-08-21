#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <klee/klee.h>

#define BUFFER_SIZE 16

int global;

int foo(int u) {
	global = 1;
	if (u==0) {
		return 0;
	} else {
		return 1;
	}
}

int main() {
	global = 0;
	int y = klee_int("y");
	int x = foo(y);
	if ((global == 0) && (x == 0)) {
		__assert_fail("Success", __FILE__, __LINE__, __func__);
	}
}

