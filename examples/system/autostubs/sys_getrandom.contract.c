#include "contracts.h"
i64 sys_getrandom(char * buf, i64 count, i32 flags) {
	// Preamble
	i64 size(buf) = SE_size_obj(buf) - ((uintptr_t)buf - SE_base_obj(buf));
	bool b;
	int idx;
	i64 last(buf,write);
	HAVOC(last(buf,write));
	assume(last(buf,write) >= 0);
	i64 __0_i;
	HAVOC(__0_i);
	i64 last(buf,read);
	HAVOC(last(buf,read));
	// Preconditions
	// Error state for buf:
	if(SE_SAT((1 && (0 + 1 * count + 0 * flags + -1 * last(buf,write) + 0 * size(buf) >= 0) && (-1 + 0 * count + 0 * flags + 1 * last(buf,write) + -1 * size(buf) >= 0) && (3 + 0 * count + -1 * flags + 0 * last(buf,write) + 0 * size(buf) >= 0) && (33554431 + 0 * count + 0 * flags + -1 * last(buf,write) + 0 * size(buf) >= 0)))) {
		warn("Invalid pointer buf");
	}
	// Error state for buf:
	if(SE_SAT((1 && (-1 + 0 * count + 0 * flags + 1 * last(buf,write) + -1 * size(buf) >= 0) && (0 + 1 * count + 0 * flags + -1 * last(buf,write) + 0 * size(buf) >= 0) && (3 + 0 * count + -1 * flags + 0 * last(buf,write) + 0 * size(buf) >= 0)))) {
		warn("Invalid pointer buf");
	}
	// Modifications
	if (1 && (0 + 1 * count + 0 * flags + -1 * last(buf,write) >= 0) && (3 + 0 * count + -1 * flags + 0 * last(buf,write) >= 0)){
		HAVOC_SIZE(buf, last(buf,write));
	}
	// Postconditions
	HAVOC(b);
	if (b) {
		return __0_i;
	}
	assume(0);
	return 0; // Unreachable
}
i64 __sys_getrandom_va_wrapper(va_list args) {
	char * buf = va_arg(args, char *);
	i64 count = va_arg(args, i64);
	i32 flags = va_arg(args, i32);
	return sys_getrandom(buf, count, flags);
}
