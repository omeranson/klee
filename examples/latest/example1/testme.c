#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <klee/klee.h>

/*
#define BUFFER_SIZE 16

char * input(const char * name) {
	size_t size = BUFFER_SIZE*sizeof(char);
	char * buffer = (char*)malloc(size);
	klee_make_symbolic(buffer, size, name);
	return buffer;
}
*/
int _strcmp(char *str1, char *str2) {
	while (*str1 != '\0'
			&& *str2 != '\0'
			&& *str1 == *str2) {
		str1++; str2++;
	}
	return *str1 - *str2;
}

void testme() {
	int tmp1, tmp2;
	char *s1, * s2;
	char *const1 = "Hello World";
	char *const2 = "Hello ESEC/FSE";
	s1 = klee_string("s1");
	s2 = klee_string("s2");
	tmp1 = _strcmp(s1,const1);
	tmp2 = _strcmp(s2,const2);
	if (tmp1 == 0)
	{
		if (tmp2 == 0)
		{
			printf("Success");
			__assert_fail("Success", __FILE__, __LINE__, __func__);
		}
	}
}

int main(int argc, char * argv[]) {
	testme();
}

