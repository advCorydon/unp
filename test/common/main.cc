#include "Error.H"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	cout<<"Hello World"<<endl;
	
	Error::terminate("say error %s <IPaddress>", argv[0]);
	
	return 0;
}
