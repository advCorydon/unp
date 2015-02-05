#include "Error.H"
#include "Constants.H"
#include "SocketWrapper.H"
#include "StdioWrapper.H"
#include "Utility.H"
#include "ReadLine.H"
#include "unp.H"

#include <iostream>
#include <stdio.h>
#include <sys/select.h>
#include <algorithm>
#include <netinet/in.h>

using namespace Constants;
using namespace std;

void strCli(FILE* fp, int sockFd){
	int maxfdp1;
	fd_set rset;
	char sendLine[MAX_LINE];
	char receiveLine[MAX_LINE];
	
	FD_ZERO(&rset);
	
	while(true){
		FD_SET(fileno(fp), &rset);
		FD_SET(sockFd, &rset);
		
		maxfdp1 = max(fileno(fp), sockFd) + 1;
		
		SocketWrapper::select(maxfdp1, &rset, NULL, NULL, NULL);
		
		if(FD_ISSET(sockFd, &rset)){
			if(ReadLine::readline(sockFd, receiveLine, sizeof(receiveLine)) == 0){
				Error::terminate("strCli: server terminated prematurely");
			}
			
			StdioWrapper::fputs(receiveLine, stdout);
		}
		
		if(FD_ISSET(fileno(fp), &rset)){
			if(StdioWrapper::fgets(sendLine, sizeof(sendLine), fp) == NULL){
				return;
			}
			
			Utility::writeNEH(sockFd, sendLine, strlen(sendLine));
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
