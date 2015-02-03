#ifndef ERROR_H__
#define ERROR_H__

#include <stdarg.h>
#include <cstring>

class Error{
public:
	static void sysInfo(const char* fmt, ...);
	static void sysTerminate(const char* fmt, ...);
	static void sysDump(const char* fmt, ...);
	static void info(const char* fmt, ...);
	static void terminate(const char* fmt, ...);
private:
	static void errDoit(int, int, const char*, va_list);
};

#endif
