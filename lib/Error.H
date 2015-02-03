#ifndef ERROR_H__
#define ERROR_H__

#include <stdarg.h>
#include <cstring>

class Error{
public:
	static void errRet(const char* fmt, ...);
private:
	static void errDoit(int, int, const char*, va_list);
};

#endif
