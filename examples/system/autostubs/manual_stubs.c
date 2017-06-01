#include <errno.h>
#include <netdb.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <klee/klee.h>

#include "contracts.h"

#define F_PERM 1
#define F_NORD 4
#define F_NOWR 8
#define F_EOF 16
#define F_ERR 32
#define F_SVB 64
#define F_APP 128

struct _IO_FILE {
	unsigned flags;
	unsigned char *rpos, *rend;
	int (*close)(FILE *);
	unsigned char *wend, *wpos;
	unsigned char *mustbezero_1;
	unsigned char *wbase;
	size_t (*read)(FILE *, unsigned char *, size_t);
	size_t (*write)(FILE *, const unsigned char *, size_t);
	off_t (*seek)(FILE *, off_t, int);
	unsigned char *buf;
	size_t buf_size;
	FILE *prev, *next;
	int fd;
	int pipe_pid;
	long lockcount;
	short dummy3;
	signed char mode;
	signed char lbf;
	volatile int lock;
	volatile int waiters;
	void *cookie;
	off_t off;
	char *getln_buf;
	void *mustbezero_2;
	unsigned char *shend;
	off_t shlim, shcnt;
	FILE *prev_locked, *next_locked;
	struct __locale_struct *locale;
};

size_t __stdio_write(FILE *f, const unsigned char *buf, size_t len) {
	size_t result;
	klee_make_symbolic(&result, sizeof(result), __FUNCTION__);
	if (result == len) {
		f->wend = f->buf + f->buf_size;
		f->wpos = f->wbase = f->buf;
	} else if (result < len) {
		f->wpos = f->wbase = f->wend = 0;
		f->flags |= F_ERR;
		errno = klee_int(__FUNCTION__);
	} else {
		klee_silent_exit(0);
	}
	return result;
}

int atoi(const char *nptr) {
	strlen(nptr);
	errno = klee_int(__FUNCTION__);
	return klee_int(__FUNCTION__);
}

double atof(const char *nptr) {
	strlen(nptr);
	double result;
	klee_make_symbolic(&result, sizeof(result), __FUNCTION__);
	errno = klee_int(__FUNCTION__);
	return result;
}

long long
strtonum(const char *nptr, long long minval, long long maxval,
		const char **errstr) {
	strlen(nptr);
	long long result;
	klee_make_symbolic(&result, sizeof(result), __FUNCTION__);
	if ((result > maxval) || (result < minval)) {
		if (errstr) {
			*errstr = "Error in strtonum";
		}
		errno = klee_int(__FUNCTION__);
		return 0;
	}
	if (errstr) {
		*errstr = 0;
	}
	return result;
}

double strtod(const char *nptr, char **endptr) {
	int len = strlen(nptr);
	double result;
	HAVOC(result);
	if (endptr) {
		assume(endptr >= nptr);
		assume(endptr <= &nptr[len]);
	}
	return result;
}

float strtof(const char *nptr, char **endptr) {
	int len = strlen(nptr);
	float result;
	HAVOC(result);
	if (endptr) {
		assume(endptr >= nptr);
		assume(endptr <= &nptr[len]);
	}
	return result;
}

long double strtold(const char *nptr, char **endptr) {
	int len = strlen(nptr);
	long double result;
	HAVOC(result);
	if (endptr) {
		assume(endptr >= nptr);
		assume(endptr <= &nptr[len]);
	}
	return result;
}

