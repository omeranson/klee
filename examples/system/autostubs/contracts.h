#include <stdarg.h>
#include <stdint.h>
#include <assert.h>
#include <sys/uio.h>
#include <sys/socket.h>

#include <klee/klee.h>

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;
typedef unsigned char bool;

#define size(buf) __size__##buf
#define offset(ptr,buf) __offset__##ptr##__to__##buf
#define last(buf,op) __last__##buf##__##op

#define assume(p) if (!(p)) klee_silent_exit(p)
#define warn(msg, ptr) klee_report_error(__FILE__, __LINE__, msg, "contract")
#define SE_size_obj(buf) (buf ? klee_get_obj_size(klee_get_obj_base(buf)) : 0)
#define SE_base_obj(buf) (buf ? klee_get_obj_base(buf) : 0)
static inline int SE_SAT(cond) {
	char b;
	klee_make_symbolic(&b, sizeof(b), "SE_SAT");
	if (b) {
		assume(cond);
	}
	return b;
}

#include "stubs_helper_macros.h"

