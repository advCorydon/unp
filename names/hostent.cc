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
#include <netdb.h>

using namespace Constants;
using namespace std;


int main(int argc, char* argv[]){
	if(argc < 2){
		Error::terminate("Usage: %s <hosts>", argv[0]);
	}
	
	for(int i = 1; i < argc; i++){
		char* ptr = argv[i];
		struct hostent* hptr = gethostbyname(ptr);
		if(ptr == NULL){
			Error::info("gethostbyname error for host: %s : %s",
					ptr, hstrerror(h_errno));
			continue;
		}
		
		cout<<"official hostname:"<<hptr->h_name<<endl;
		for(char** pptr = hptr->h_aliases; *pptr != NULL; pptr++){
			cout<<"alias:"<<*pptr<<endl;
		}
		
		char** pptr;
		switch(hptr->h_addrtype){
			case AF_INET:
				pptr = hptr->h_addr_list;
				for(; *pptr != NULL; pptr++){
					char str[INET_ADDRSTRLEN];
					cout<<"address:" <<SocketWrapper::inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str))<<endl;
				}
				break;
			default:
				Error::info("unknown address type");
				break;
		}
	}
	
	return 0;
}		
