#include <unistd.h>
#include "UnixWrapper.H"
#include "Error.H"

void UnixWrapper::write(int fd, const void *ptr, ssize_t nbytes)
{
	if(::write(fd, ptr, nbytes) != nbytes){
		Error::sysTerminate("write error");
	}
}

ssize_t UnixWrapper::read(int fd, void* ptr, size_t nbytes){
	ssize_t n = ::read(fd, ptr, nbytes);
	if(n == -1){
		Error::sysTerminate("read error");
	}
	
	return n;
}

void UnixWrapper::close(int fd){
	if(::close(fd) < 0){
		Error::sysTerminate("close error");
	}
}
