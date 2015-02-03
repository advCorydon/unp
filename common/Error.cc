#include "Error.H"
#include "Constants.H"

#include <syslog.h>
#include <string>
#include <iostream>
//#include <cstring>
#include <cstdio>
#include <cerrno>
#include <cstdlib>

using namespace std;

/* Nonfatal error related to system call
 * Print message and return */
void Error::sysInfo(const char* fmt, ...){
	va_list ap;
	
	va_start(ap, fmt);
	errDoit(1, LOG_INFO, fmt, ap);
	va_end(ap);
	
	return;
}

/*Fatal error related to system call
 *Print message and terminate */
void Error::sysTerminate(const char* fmt, ...){
	va_list ap;
	
	va_start(ap, fmt);
	errDoit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(1);
}

/* Fatal error related to system call
 * Print message, dump core and terminate */
void Error::sysDump(const char* fmt, ...){
	va_list ap;
	
	va_start(ap, fmt);
	errDoit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	abort();
	exit(1);
}

/* Nonfata error unrelated to system call
 * Print message and return */
void Error::info(const char* fmt, ...){
	va_list ap;
	
	va_start(ap, fmt);
	errDoit(0, LOG_INFO, fmt, ap);
	va_end(ap);
	
	return;
}

/* Fatal error unrelated to system call
 * Print message and terminate */
void Error::terminate(const char* fmt, ...){
	va_list ap;
	
	va_start(ap, fmt);
	errDoit(0, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(1);
}

/* Print message and return to caller
 * Caller specifies "errnoflag" and "level" */
void Error::errDoit(int errnoFlag, int level, const char* fmt, va_list ap){
	int errnoSave = errno;
	char buffer[Constants::MAX_LINE + 1];
	
	vsnprintf(buffer, Constants::MAX_LINE, fmt, ap);
	
	string message(buffer);
	if(errnoFlag){
		message += " : ";
		message += strerror(errnoSave);
	}
	
	
	cout<<message<<endl;
	
	return;
}
