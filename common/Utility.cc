#include "Utility.H"
#include "Constants.H"
#include "Error.H"
#include "StdioWrapper.H"
#include "ReadLine.H"

#include <error.h>
#include <errno.h>


void Utility::strEcho(int sockfd){
	char buf[Constants::MAX_LINE];
	while(true){
		ssize_t n = 0;
		while( (n = read(sockfd, buf, Constants::MAX_LINE)) > 0){
			if(writeN(sockfd, buf, n) != n){
				Error::sysInfo("StrEcho: writeN error");
			}
		}
		
		if(n == 0){
			break;
		}
		
		if(errno != EINTR){
			Error::sysInfo("strEcho: read error");
		}					
	}
	
	return;
}


ssize_t Utility::writeN(int fd, const void* vptr, size_t n){
	const char* ptr = static_cast<const char*>(vptr);
	size_t left = n;
	while(left > 0){
		size_t written = write(fd, ptr, left);
		if(written < 0){
			if(errno == EINTR){
				written = 0;
			}
			else{
				return -1;
			}
		}
		
		left -= written;
		ptr += written;
	}
	
	return n;
}

void Utility::writeNEH(int fd, const void* ptr, size_t n){
	if(writeN(fd, ptr, n) != n){
		Error::sysInfo("write error.");
	}
}

void Utility::strCli(FILE* fp, int sockfd){
	char sendLine[Constants::MAX_LINE];
	char receiveLine[Constants::MAX_LINE];
		
	while(StdioWrapper::fgets(sendLine, Constants::MAX_LINE, fp) != NULL){
		writeNEH(sockfd, sendLine, strlen(sendLine));
		
		if(ReadLine::readLineEH(sockfd, receiveLine, Constants::MAX_LINE) == 0){
			Error::terminate("strCli: server terminated prematurely");
		}
		
		StdioWrapper::fputs(receiveLine, stdout);
	}
}

	
		
		
