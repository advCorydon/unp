#include "Error.H"
#include "Constants.H"
#include "SocketWrapper.H"
#include "Utility.H"
#include "unp.H"

#include <netinet/in.h>
#include <iostream>

using namespace std;


int main(int argc, char* argv[]){
	if(argc != 2){
		Error::terminate("usage: %s <IP address>", argv[0]);
	}
	int fds[5];
	
	for(int i = 0; i < 5; i++){
		fds[i] = SocketWrapper::socket(AF_INET, SOCK_STREAM, 0);
			
		struct sockaddr_in serverAddr;
		bzero(&serverAddr, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(Constants::SERVER_PORT);
		SocketWrapper::inet_pton(AF_INET, argv[1], &serverAddr.sin_addr);
		
		SocketWrapper::connect(fds[i], (SA*)(&serverAddr), sizeof(serverAddr));
	}
		
	Utility::strCli(stdin, fds[0]);
	
	exit(0);	
}
