#include <stdarg.h>
#include <stdint.h>
#include <assert.h>

#include <klee/klee.h>

typedef long long i64;
typedef long i32;
typedef unsigned char bool;

#define size(buf) __size__##buf
#define offset(buf) __offset__##buf
#define last(buf,op) __last__##buf##__##op

#define assume(p) if (!p) klee_silent_exit(p)
#define warn(msg) klee_report_error(__FILE__, __LINE__, msg, "contract")
//uintptr_t SE_size_obj(void * buf);
//uintptr_t SE_base_obj(void * buf);
#define SE_size_obj(buf) klee_get_obj_size(buf)
#define SE_base_obj(buf) klee_get_obj_base(buf)
int SE_SAT(cond) {
	char b;
	klee_make_symbolic(&b, sizeof(b), "SE_SAT");
	if (b) {
		assume(cond);
	}
	return b;
}

#include "stubs_helper_macros.h"

