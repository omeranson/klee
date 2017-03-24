#include <errno.h>
#include <netdb.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <klee/klee.h>

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
int sscanf(const char *str, const char *format, ...) {
	va_list ap;
	int * p_d;
	float * p_f;
	double * p_lf;
	errno = klee_int(__FUNCTION__);
	int result = klee_int(__FUNCTION__);
	klee_assume(result >= -1);
	klee_assume(result <= 7);
	va_start(ap, format);
	p_d = va_arg(ap, int*);
	klee_make_symbolic(p_d, sizeof(int), __FUNCTION__);
	p_f = va_arg(ap, float*);
	klee_make_symbolic(p_f, sizeof(float), __FUNCTION__);
	p_f = va_arg(ap, float*);
	klee_make_symbolic(p_f, sizeof(float), __FUNCTION__);
	p_f = va_arg(ap, float*);
	klee_make_symbolic(p_f, sizeof(float), __FUNCTION__);
	p_lf = va_arg(ap, double*);
	klee_make_symbolic(p_lf, sizeof(double), __FUNCTION__);
	p_f = va_arg(ap, float*);
	klee_make_symbolic(p_f, sizeof(float), __FUNCTION__);
	p_d = va_arg(ap, int*);
	klee_make_symbolic(p_d, sizeof(int), __FUNCTION__);
	va_end(ap);
	return result;
}
// n=sscanf(line,"%d %f %f %f %lf %f %d",                          
//         &day, &sec, &el_time, &st_time, &skew, &disp, &freq);   

int atoi(const char *nptr) {
	//strlen(nptr);
	errno = klee_int(__FUNCTION__);
	return klee_int(__FUNCTION__);
}

double atof(const char *nptr) {
	//strlen(nptr);
	double result;
	klee_make_symbolic(&result, sizeof(result), __FUNCTION__);
	errno = klee_int(__FUNCTION__);
	return result;
}

struct hostent *gethostbyname(const char *name) {
	// Watered down for NTP client only.
	int isFail;
	klee_make_symbolic(&isFail, sizeof(isFail), __FUNCTION__);
	if (isFail == 0) {
		struct hostent * result = malloc(sizeof(*result));
		result->h_name = malloc(256);
		klee_make_symbolic(result->h_name, 256, __FUNCTION__);
		result->h_aliases = 0;
		result->h_addrtype = klee_int(__FUNCTION__);
		if (result->h_addrtype == AF_INET) {
			result->h_length = 4;
		} else if (result->h_addrtype == AF_INET6) {
			result->h_length = 16;
		} else {
			klee_silent_exit(0);
		}
		result->h_addr_list = malloc(2*sizeof(char*));
		result->h_addr_list[0] = malloc(result->h_length);
		klee_make_symbolic(result->h_addr_list[0], result->h_length, __FUNCTION__);
		result->h_addr_list[1] = 0;
		return result;
	} else if (isFail == 1) {
		errno = klee_int(__FUNCTION__);
		return 0;
	}
	klee_silent_exit(0);
}
