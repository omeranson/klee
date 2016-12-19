#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <klee/klee.h>

/*
#define BUFFER_SIZE 16

char * klee_string1(const char * name) {
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

int global = 0;
int strcmp_wrapper(char * str1, char * str2) {
	global++;
	return _strcmp(str1, str2);
}

void testme() {
	int tmp1, tmp2, tmp3;
	char *s1, *s2, *s3;
	char *const1 = "Hello World";
	char *const2 = "Hello ESEC/FSE";
	char *const3 = "How are you?";
	s1 = klee_string(16, "s1");
	s2 = klee_string(16, "s2");
	s3 = klee_string(16, "s3");
	tmp1 = strcmp_wrapper(s1,const1);
	tmp2 = strcmp_wrapper(s2,const2);
	tmp3 = strcmp_wrapper(s3,const3);
	if (tmp1 == 0)
	{
		if (tmp2 == 0)
		{
			if (tmp3 == 0)
			{
				printf("Success");
				__assert_fail("Success", __FILE__, __LINE__, __PRETTY_FUNCTION__);
			}
		}
	}
}

int main(int argc, char * argv[]) {
	testme();
}

