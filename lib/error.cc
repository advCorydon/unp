#include "unp.H"
#include <stdarg.h>
#include <syslog.h>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cerrno>

using namespace std;

static void errDoit(int, int, const char*, va_list);

void errRet(const char* fmt, ...){
	va_list ap;
	
	va_start(ap, fmt);
	errDoit(1, LOG_INFO, fmt, ap);
	va_end(ap);
	
	return;
}

/* Print message and return to caller
 * Caller specifies "errnoflag" and "level" */
static void errDoit(int errnoFlag, int level, const char* fmt, va_list ap){
	int errnoSave = errno;
	char buffer[MAX_LINE + 1];
	
	vsnprintf(buffer, MAX_LINE, fmt, ap);
	
	string message(buffer);
	if(errnoFlag){
		message += strerror(errnoSave);
	}
	
	cout<<message<<endl;
	
	return;
}
