#include "Error.H"
#include "Constants.H"
#include "unp.H"
#include "Utility.H"
#include "SocketWrapper.H"
#include "UnixWrapper.H"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;
using namespace Constants;

void sigChld(int signo);

int main(int argc, char* argv[]){
	cout<<"FD_SETSIZE:"<<FD_SETSIZE<<endl;
	
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
	
	signal(SIGCHLD, sigChld);
	
	int maxFd = listenFd;
	int maxi = -1;
	int client[FD_SETSIZE];
	for(int i = 0; i < FD_SETSIZE; i++){
		client[i] = -1;
	}
	
	fd_set allSet;
	FD_ZERO(&allSet);
	FD_SET(listenFd, &allSet);
	
	while(1){
		fd_set rset = allSet;
		int nReady = SocketWrapper::select(maxFd + 1, &rset, NULL, NULL, NULL);
		if(FD_ISSET(listenFd, &rset)){
			struct sockaddr_in clientAddr;
			socklen_t len = sizeof(clientAddr);
			int connFd = SocketWrapper::accept(listenFd, (SA*)(&clientAddr), &len);
			cout<<"INFO: accept return. connect fd:"<<connFd<<endl;
			
			int i = 0;
			for(; i < FD_SETSIZE; i++){
				if(client[i] < 0){
					client[i] = connFd;
					break;
				}
			}
			
			if(i == FD_SETSIZE){
				Error::terminate("too many clients");
			}
			
			FD_SET(connFd, &allSet);
			maxFd = connFd > maxFd ? connFd : maxFd;
			if( i > maxi){
				maxi = i;
			}
			
			if(--nReady <= 0){
				continue;
			}
		}
		
		for(int i = 0; i <= maxi; i++){
			if(client[i] < 0){
				continue;
			}
			
			int sockFd = client[i];
			if(FD_ISSET(sockFd, &rset)){
				char buffer[MAX_LINE];
				int n = UnixWrapper::read(sockFd, buffer, MAX_LINE);
				if( n == 0){
					UnixWrapper::close(sockFd);
					FD_CLR(sockFd, &allSet); 
					client[i] = -1;
				}
				else{
					Utility::writeNEH(sockFd, buffer, n);
				}
				
				if( --nReady <= 0){
					break;
				}
			}
		}
	}
		
}

void sigChld(int signo){
	pid_t pid;
	int stat;
	
	pid = wait(&stat);
	printf("child %d terminated\n", pid);
	return;
}
