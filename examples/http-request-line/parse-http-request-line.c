#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#include <klee/klee.h>

// typedef struct {
// 	char * method;
// 	char * requesturi;
// 	char * version;
// } http_request_t;

int _strlen(char *s) {
	int n = 0;
	for (; *s; s++) {
		n++;
	}
	return n;
}

int _strcmp(char *str1, char *str2) {
	while (*str1 != '\0'
			&& *str2 != '\0'
			&& *str1 == *str2) {
		str1++; str2++;
	}
	return *str1 - *str2;
}

int _strncmp(char *str1, char *str2, int n) {
	while (n-- && *str1 != '\0'
			&& *str2 != '\0'
			&& *str1 == *str2) {
		str1++; str2++;
	}
	return *str1 - *str2;
}

char * _strchr(char * s, int c) {
	for (; *s; s++) {
		if (*s == c) {
			return s;
		}
	}
	if (*s == c) {
		return s;
	}
	return 0;
}

//char * next_separator(char * str) {
//	for (; *str; str++) {
//		if (' ' == *str) {
//			return str;
//		}
//	}
//	return 0;
//}
//
//int parse_http_request_str(char *request_str,
//		char ** method, char ** uri, char ** version) {
//	*method = request_str;
//
//	request_str = next_separator(request_str);
//	if (!request_str || *request_str != ' ') {
//		return -1;
//	}
//	*request_str++ = '\0';
//	*uri = request_str;
//
//	request_str = next_separator(request_str);
//	if (!request_str || *request_str != ' ') {
//		return -1;
//	}
//	*request_str++ = '\0';
//	*version = request_str;
//
//	request_str = next_separator(request_str);
//	if (!request_str || *request_str != '\r') {
//		return -1;
//	}
//	*request_str++ = '\0';
//	if (*request_str != '\n') {
//		return -1;
//	}
//	return 0;
//}

int parse_http_request_str(char *request_str,
		char ** method, char ** uri, char ** version) {
	*method = request_str;

	// next separator
	for (; ' ' != *request_str; request_str++) {
		if (!*request_str) {
			return -1;
		}
	}
	*request_str++ = '\0';
	*uri = request_str;

	// next separator
	for (; ' ' != *request_str; request_str++) {
		if (!*request_str) {
			return -1;
		}
	}
	*request_str++ = '\0';
	*version = request_str;

	// next separator
	for (; '\r' != *request_str; request_str++) {
		if (!*request_str) {
			return -1;
		}
	}
	*request_str++ = '\0';
	if (*request_str != '\n') {
		return -1;
	}
	return 0;
}

int verify_method(char * method) {
	if (_strcmp(method, "OPTIONS") == 0) {
		return 0;
	}
	if (_strcmp(method, "GET") == 0) {
		return 0;
	}
	if (_strcmp(method, "HEAD") == 0) {
		return 0;
	}
	if (_strcmp(method, "POST") == 0) {
		return 0;
	}
	if (_strcmp(method, "PUT") == 0) {
		return 0;
	}
	if (_strcmp(method, "DELETE") == 0) {
		return 0;
	}
	if (_strcmp(method, "TRACE") == 0) {
		return 0;
	}
	if (_strcmp(method, "CONNECT") == 0) {
		return 0;
	}
	return -1;
}

int verify_uri(char * uri) {
	return 0; // Always legal, for now
}

int verify_version(char * version) {
	if (_strlen(version) != sizeof("HTTP/X.Y")) {
		return -1;
	}
	if (_strncmp(version, "HTTP/", sizeof("HTTP/")-1) != 0) {
		return -1;
	}
	//if (!isdigit(version[5]))
	if ((version[5] < '0') || (version[5] > '9')) {
		return -1;
	}
	if (version[6] != '.') {
		return -1;
	}
	//if (!isdigit(version[7]))
	if ((version[7] < '0') || (version[7] > '9')) {
		return -1;
	}
	return 0;
}

void parse_http_request(char * request_str) {
	char * method = 0;
	char * uri = 0;
	char * version = 0;
	int result = parse_http_request_str(request_str,
			&method, &uri, &version);
	//if (result == 0) {
	//	if (method < request_str) {
	//		result = -1;
	//	}
	//}
	if (result == 0) {
		result = verify_method(method);
	}
	if (result == 0) {
		result = verify_uri(uri);
	}
	if (result == 0) {
		result = verify_version(version);
	}
	if (result != 0) {
		fprintf(stderr, "Failed to parse http request\n");
		return;
	}
	printf("Method: %s\n", method);
	printf("URI: %s\n", uri);
	printf("Version: %s\n", version);
	__assert_fail("Success", __FILE__, __LINE__, __PRETTY_FUNCTION__);
	return;
}

int main() {
	char * request = klee_string(20, "request");
	parse_http_request(request);
	return 0;
}
