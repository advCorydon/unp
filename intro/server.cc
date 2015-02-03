#include "Error.H"
#include "unp.H"
#include "Constants.H"
#include <time.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;


int main(int argc, char* argv[]){
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd <0){
		Error::sysTerminate("socket error");
	}
	
	struct sockaddr_in serverAddr;
	bzero(&serverAddr, sizeof(serverAddr));
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(13);
	
	if(bind(listenfd, (SA*)&serverAddr, sizeof(serverAddr)) < 0){
		Error::sysTerminate("bind error");
	}
	
	if(listen(listenfd, Constants::LISTENQ) < 0){
		Error::sysTerminate("listen error");
	}
	
	while(1){
		int connfd = accept(listenfd, static_cast<SA*>(NULL), NULL);
		if(connfd < 0){
			Error::sysTerminate("accept error");
		}
		
		time_t ticks = time(NULL);
		char buffer[Constants::MAX_LINE];
		snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
		
		if(write(connfd, buffer, strlen(buffer)) < 0){
			Error::sysTerminate("write error");
		}
		
		cout<<"Write message:"<<buffer<<endl;
		
		if(close(connfd) < 0){
			Error::sysTerminate("close error");
		}
	}
}
