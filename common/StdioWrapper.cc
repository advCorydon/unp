#include "StdioWrapper.H"
#include "Error.H"

char* StdioWrapper::fgets(char *ptr, int n, FILE *stream){
	char    *rptr;
	if ( (rptr = ::fgets(ptr, n, stream)) == NULL && ferror(stream)){
	    Error::sysTerminate("fgets error");
	}
	
	return rptr;
}


void StdioWrapper::fputs(const char *ptr, FILE *stream){
	if (::fputs(ptr, stream) == EOF){
		Error::sysTerminate("fputs error");
	}
}
