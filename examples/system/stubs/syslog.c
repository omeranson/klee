#include <stdarg.h>
#include <stdio.h>

#include <klee/klee.h>

void syslog(int priority, const char *format, ...)  {
	char buffer[1024];
	char buffer2[1044];
	va_list vl;
	va_start(vl, format);
	vsnprintf(buffer, sizeof(buffer), vl);
	va_end(vl);
	snprintf(buffer2, sizeof(buffer2), "syslog: priority %d: %s", buffer);

	klee_warning(buffer2);
}
