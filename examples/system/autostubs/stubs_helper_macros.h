#include <alloca.h>
#include <string.h>

#include <klee/klee.h>

#define HAVOC(dest) do { \
	klee_make_symbolic(&dest, sizeof(dest), #dest); \
} while (0)

#define HAVOC_SIZE(dest, size) do { \
	klee_make_symbolic(SE_base_obj(dest), SE_size_obj(dest), #dest); \
} while (0)

#define HAVOC_NEW_STRING_SIZE(dest, size) do { \
	char * __result = malloc(size); \
	klee_make_symbolic(__result, size, #dest); \
	__result[size-1] = '\0'; \
	dest = __result; \
} while (0)
/*
#define RETURN_VALUES_EXPAND_OPTIONS(arg, ...) \
	(retval == arg) || RETURN_VALUES_EXPAND_OPTIONS(__VA_ARGS__)

#define RETURN_VALUES(...) do { \
	int retval = klee_int(); \
	klee_assume(RETURN_VALUES_EXPAND_OPTIONS(__VA_ARGS__)); \
	return retval; \
while (0)
*/
