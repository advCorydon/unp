#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "Error.H"
#include "Constants.H"


using namespace std;

typedef struct sockaddr SA;

int main(int argc, char* argv[]){
	if(argc != 2){
		Error::terminate("usage: %s <IPaddress> ", argv[0]);
	}
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		Error::sysTerminate("socket error");
	}
	
	struct sockaddr_in serverAddr;
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(13);
	if(inet_pton(AF_INET, argv[1], &serverAddr.sin_addr) <= 0){
		Error::terminate("inet_pton error for %s ", argv[1]);
	}
	
	if(connect(sockfd, (SA*)&serverAddr, sizeof(serverAddr)) < 0){
		Error::sysTerminate("connect error");
	}
	
	int n = 0;
	int count = 0;
	char recvLine[Constants::MAX_LINE + 1];	
	while( (n = read(sockfd, recvLine, Constants::MAX_LINE)) > 0){
		recvLine[n] = '\0';
		count++;
		cout<<recvLine;
	}
	cout<<"counter = "<< count <<endl;
	
	if(n < 0){
		Error::sysTerminate("Read error");
	}
	
	exit(0);
	
}