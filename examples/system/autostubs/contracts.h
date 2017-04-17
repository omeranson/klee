#include <stdarg.h>
#include <stdint.h>
#include <assert.h>

typedef long long i64;
typedef long i32;
typedef unsigned char bool;

#define size(buf) __size__##buf
#define offset(buf) __offset__##buf
#define last(buf,op) __last__##buf##__##op

#define assume(p) if (!p) klee_silent_exit(p)
//uintptr_t SE_size_obj(void * buf);
//uintptr_t SE_base_obj(void * buf);
#define SE_size_obj(buf) sizeof(int)
#define SE_base_obj(buf) (uintptr_t)buf

#include "stubs_helper_macros.h"

