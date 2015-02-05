#ifndef SOCKET_WRAPPER_H__
#define SOCKET_WRAPPER_H__

#include <sys/types.h>
#include <sys/socket.h>

class SocketWrapper{
public:
	static int socket(int family, int type, int protocol);
	
	static void inet_pton(int family, const char* str, void* dst);
	
	static void connect(int sockfd, const struct sockaddr *addr, socklen_t len);
	
	static int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
};

#endif
