#include "Error.H"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	cout<<"Hello World"<<endl;
	
	Error::errRet("say error");
	
	return 0;
}
