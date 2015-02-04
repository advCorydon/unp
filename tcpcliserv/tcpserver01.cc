#include "Error.H"
#include "Constants.H"
#include "unp.H"
#include "Utility.H"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, char* argv[]){
	int listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenFd < 0){
		Error::sysInfo("socket error");
	}
	
	struct sockaddr_in serverAddr;
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(Constants::SERVER_PORT);
	
	if(bind(listenFd, (SA*)(&serverAddr), sizeof(serverAddr)) < 0){
		Error::sysInfo("bind error");
	}
	
	if(listen(listenFd, Constants::LISTENQ) < 0){
		Error::sysInfo("listen error");
	}
	
	while(1){
		struct sockaddr_in clientAddr;
		socklen_t len = sizeof(clientAddr);
		int connFd = accept(listenFd, (SA*)(&clientAddr), &len);
		if(connFd < 0){
			Error::sysInfo("accept error");
		}
		
		pid_t childPid = fork();
		if(childPid < 0){
			Error::sysInfo("fork error");
		}
		else if(childPid == 0){
			close(listenFd);
			Utility::strEcho(connFd);
			exit(0);
		}
		else{
			close(connFd);
		}
	}
		
}
