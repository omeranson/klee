#define HAVOC(dest) do { \
	void * temp = alloca(sizeof(*dest)); \
	klee_make_symbolic(temp, sizeof(*dest), __FUNCTION__); \
	memcpy(dest, temp, sizeof(*dest)); \
} while (0)

#define HAVOC_SIZE(dest, size) do { \
	void * temp = alloca(size); \
	klee_make_symbolic(temp, size, __FUNCTION__); \
	memcpy(dest, temp, size); \
} while (0)

#define HAVOC_NEW_STRING_SIZE(dest, size) do { \
	char * __result = malloc(size); \
	klee_make_symbolic(__result, size, __FUNCTION__); \
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
