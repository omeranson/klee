#include <errno.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


#include <klee/klee.h>

#include "stubs_helper_macros.h"

struct passwd *getpwnam(const char *name) {
	strlen(name);
	int isfail = klee_int(__FUNCTION__);
	if (isfail == 0) {
		struct passwd * result = malloc(sizeof(*result));
		HAVOC_NEW_STRING_SIZE(result->pw_name, 128);
		HAVOC_NEW_STRING_SIZE(result->pw_passwd, 128);
		HAVOC_NEW_STRING_SIZE(result->pw_gecos, 128);
		HAVOC_NEW_STRING_SIZE(result->pw_dir, 128);
		HAVOC_NEW_STRING_SIZE(result->pw_shell, 128);
		HAVOC(&(result->pw_uid));
		HAVOC(&(result->pw_gid));
		return result;
	} else if (isfail == 1) {
		errno = klee_int(__FUNCTION__);
		return 0;
	} else {
		klee_silent_exit(0);
	}
}

void read_config( char* filename ) {
	return;
}

int getaddrinfo(const char *node, const char *service,
		const struct addrinfo *hints,
		struct addrinfo **res) {
	// Watered down for thttpd
	struct addrinfo * ai4;
	struct addrinfo * ai6;
	int has_ipv4 = klee_int(__FUNCTION__);
	int has_ipv6 = klee_int(__FUNCTION__);
	*res = 0;
	if (has_ipv4) {
		ai4 = malloc(sizeof(*ai4));
		ai4->ai_flags = 0;
		ai4->ai_family = AF_INET;
		ai4->ai_socktype = 0;
		ai4->ai_protocol = 0;
		ai4->ai_addrlen = 4;
		ai4->ai_addr = malloc(4);
		klee_make_symbolic(ai4->ai_addr, 4, __FUNCTION__);
		ai4->ai_canonname = malloc(128);
		klee_make_symbolic(ai4->ai_canonname, 128, __FUNCTION__);
		ai4->ai_next = 0;
		*res = ai4;
		res = &(ai4->ai_next);
	}
	if (has_ipv6) {
		ai6 = malloc(sizeof(*ai6));
		ai6->ai_flags = 0;
		ai6->ai_family = AF_INET;
		ai6->ai_socktype = 0;
		ai6->ai_protocol = 0;
		ai6->ai_addrlen = 4;
		ai6->ai_addr = malloc(4);
		klee_make_symbolic(ai6->ai_addr, 4, __FUNCTION__);
		ai6->ai_canonname = malloc(128);
		klee_make_symbolic(ai6->ai_canonname, 128, __FUNCTION__);
		ai6->ai_next = 0;
		*res = ai6;
	}
	int retval = klee_int(__FUNCTION__);
	return retval;
}

void read_throttlefile( char* tf ) {
	return;
}
