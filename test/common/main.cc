#include "Error.H"
#include "Constants.H"
#include <iostream>

using namespace std;
using namespace Constants;

int main(int argc, char* argv[]){
	char readLine[MAX_LINE];
	char* ptr = fgets(readLine, sizeof(readLine), stdin);
	cout<<readLine<<endl;
	cout<<ptr<<endl;
	//Error::terminate("say error %s <IPaddress>", argv[0]);
	return 0;
}
