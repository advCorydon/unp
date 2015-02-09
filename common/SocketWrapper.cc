#include "SocketWrapper.H"
#include "Error.H"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>


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

void SocketWrapper::shutdown(int fd, int how){
	if(::shutdown(fd, how) < 0){
		Error::sysTerminate("shutdown error");
	}
	
	return;
}


int SocketWrapper::accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int n = 0;
	while(1){
		n = ::accept(fd, sa, salenptr);
		if(n < 0){
			if(errno == EPROTO || errno == ECONNABORTED){
				continue;
			}
			else{
				Error::sysTerminate("accept error");
			}
		}
		break;
	}
	
	return n;
}


const char* SocketWrapper::inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const char *ptr;
	
	if (strptr == NULL){             /* check for old code */
		Error::terminate("NULL 3rd argument to inet_ntop");
	}
	if ( (ptr = ::inet_ntop(family, addrptr, strptr, len)) == NULL){
		Error::sysTerminate("inet_ntop error");             /* sets errno */
	}
	
	return ptr;
}
	
		