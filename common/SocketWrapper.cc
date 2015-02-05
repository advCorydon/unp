#include "SocketWrapper.H"
#include "Error.H"

#include <sys/socket.h>
#include <arpa/inet.h>


int SocketWrapper::socket(int family, int type, int protocol){
	int fd = ::socket(family, type, protocol);
	if(fd < 0){
		Error::sysTerminate("socket error");
	}
	
	return fd;
}

void SocketWrapper::inet_pton(int family, const char* str, void* dst){
	int ret = ::inet_pton(family, str, dst);
	if(ret < 0){
		Error::sysTerminate("inet_pton error for %s", str);
	}
	
	if(ret == 0){
		Error::terminate("inet_pton error for %s", str);
	}
	
	return;
}

void SocketWrapper::connect(int sockfd, const struct sockaddr *addr, socklen_t len){
	if(::connect(sockfd, addr, len) < 0){
		Error::sysTerminate("connect error");
	}
}


int SocketWrapper::select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout){
	int n;
	
	if ( (n = ::select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
	        Error::sysTerminate("select error");
	return n;              /* can return 0 on timeout */
}
	
		