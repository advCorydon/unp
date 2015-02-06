#include "Error.H"
#include "Constants.H"
#include "SocketWrapper.H"
#include "StdioWrapper.H"
#include "Utility.H"
#include "ReadLine.H"
#include "unp.H"
#include "UnixWrapper.H"

#include <iostream>
#include <stdio.h>
#include <sys/select.h>
#include <algorithm>
#include <netinet/in.h>

using namespace Constants;
using namespace std;

void strCli(FILE* fp, int sockFd){
	int stdinEof = 0;
	fd_set rset;
	FD_ZERO(&rset);
	char buffer[MAX_LINE];
	while(true){
		FD_SET(fileno(fp), &rset);
		FD_SET(sockFd, &rset);
		int maxfdp1 = max(fileno(fp), sockFd) + 1;
		
		SocketWrapper::select(maxfdp1, &rset, NULL, NULL, NULL);
			
		if(FD_ISSET(sockFd, &rset)){
			int n = UnixWrapper::read(sockFd, buffer, sizeof(buffer));
			if( n == 0){
				if(stdinEof == 1){
					return;
				}
				Error::terminate("strCli: server terminated prematurely");
			}
			
			UnixWrapper::write(fileno(stdout), buffer, n);
		}
		
		if(FD_ISSET(fileno(fp), &rset)){
			int n = UnixWrapper::read(fileno(fp), buffer, sizeof(buffer));
			if( n == 0){
				stdinEof = 1;
				SocketWrapper::shutdown(sockFd, SHUT_WR);
				FD_CLR(fileno(fp), &rset);
				continue;
			}
			
			Utility::writeNEH(sockFd, buffer, n);
		}
	}
}


int main(int argc, char* argv[]){
	if(argc != 2){
		Error::terminate("usage: %s <IP address>", argv[0]);
	}
	
	int fd = SocketWrapper::socket(AF_INET, SOCK_STREAM, 0);
		
	struct sockaddr_in serverAddr;
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(Constants::SERVER_PORT);
	SocketWrapper::inet_pton(AF_INET, argv[1], &serverAddr.sin_addr);
	
	SocketWrapper::connect(fd, (SA*)(&serverAddr), sizeof(serverAddr));
		
	strCli(stdin, fd);
	
	exit(0);	
}		
