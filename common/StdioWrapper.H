#ifndef STDIO_WRAPPER_H__
#define STDIO_WRAPPER_H__

#include <stdio.h>

class StdioWrapper{
public:
	static char* fgets(char *ptr, int n, FILE *stream);
	static void fputs(const char *ptr, FILE *stream);
};

#endif
