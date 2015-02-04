#ifndef UTILITY_H__
#define UTILITY_H__

#include <unistd.h>
#include <stdio.h>

namespace Utility{
	void strEcho(int sockfd);
	void strCli(FILE*fp, int sockfd);
	
	ssize_t writeN(int fd, const void* ptr, size_t n);
	void writeNEH(int fd, const void* ptr, size_t n);
};

#endif
