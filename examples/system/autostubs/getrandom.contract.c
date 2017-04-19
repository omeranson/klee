#include "contracts.h"
i64 getrandom(char * buf, i32 s, i32 f) {
	// Preamble
	// Preamble for buf
	i64 offset(buf) = (uintptr_t)buf - SE_base_obj(buf);
	i64 size(buf) = SE_size_obj(buf) - offset(buf);
	i64 res;
	bool b;
	int idx;
	// Preconditions
	// Error state for buf:
	assert(!(1 && (-1 + 1 * s + -1 * size(buf) >= 0) && (0 + 1 * s + 0 * size(buf) >= 0) && (4095 + 0 * s + -1 * size(buf) >= 0)) && "Invalid pointer buf");
	// Modifications
	// Modification for buf:
	i64 last(buf, write);
	HAVOC(last(buf, write));
	if (1 && (0 + -1 * last(buf,write) + 1 * s >= 0) && (0 + 1 * last(buf,write) + 0 * s >= 0) && (4096 + -1 * last(buf,write) + 0 * s >= 0)) {
		HAVOC_SIZE(buf,  last(buf, write));
	}
	// Postconditions
	HAVOC(b);
	HAVOC(res);
	if (b && (0 + 0 * res + 1 * s >= 0) && (5 + 1 * res + 0 * s >= 0) && (0 + -1 * res + 1 * s >= 0)) {
			return res;
	}
	assume(0);
	return 0; // Unreachable
}
i64 __getrandom_va_wrapper(va_list args) {
	char * buf = va_arg(args, char *);
	i32 s = va_arg(args, i32);
	i32 f = va_arg(args, i32);
	return getrandom(buf, s, f);
}
