#ifndef READ_LINE_H__
#define READ_LINE_H__

#include "Constants.H"
#include <sys/types.h>

class ReadLine{
public:
	static ssize_t readLineEH(int fd, void *ptr, size_t maxlen);
	
	static ssize_t readline(int fd, void *vptr, size_t maxlen);
	ssize_t readlinebuf(void **vptrptr);
	
private:
	static int	read_cnt;
	static char	*read_ptr;
	static char	read_buf[Constants::MAX_LINE];
	
	static ssize_t my_read(int fd, char *ptr);
};

#endif

