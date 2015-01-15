#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>


using namespace std;

typedef struct sockaddr SA;
const int MAX_LINE = 4096;

int main(int argc, char* argv[]){
	if(argc != 2){
		cout<<"usage: "<<argv[0]<<" IPaddress"<<endl;
		exit(1);
	}
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		cout<<"socket error"<<endl;
		exit(1);
	}
	
	struct sockaddr_in serverAddr;
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(13);
	if(inet_pton(AF_INET, argv[1], &serverAddr.sin_addr) <= 0){
		cout<<"inet_pton error for "<<argv[1]<<endl;
		exit(1);
	}
	
	if(connect(sockfd, (SA*)&serverAddr, sizeof(serverAddr)) < 0){
		cout<<"connect error"<<endl;
	}
	
	int n = 0;
	char recvLine[MAX_LINE + 1];
	while( (n = read(sockfd, recvLine, MAX_LINE)) > 0){
		recvLine[n] = '\0';
		cout<<recvLine;
	}
	cout<<endl;
	
	if(n < 0){
		cout<<"read error"<<endl;
	}
	
	exit(0);
	
}