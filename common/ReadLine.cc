#include "ReadLine.H"
#include "Error.H"

#include <unistd.h>
#include <errno.h>


int	ReadLine::read_cnt;
char* ReadLine::read_ptr;
char ReadLine::read_buf[Constants::MAX_LINE];
		
ssize_t ReadLine::my_read(int fd, char *ptr){

	if (read_cnt <= 0) {
again:
		if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
			if (errno == EINTR)
				goto again;
			return(-1);
		} else if (read_cnt == 0)
			return(0);
		read_ptr = read_buf;
	}

	read_cnt--;
	*ptr = *read_ptr++;
	return(1);
}

ssize_t ReadLine::readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t	n, rc;
	char	c, *ptr;

	ptr = (char*)vptr;
	for (n = 1; n < maxlen; n++) {
		if ( (rc = my_read(fd, &c)) == 1) {
			*ptr++ = c;
			if (c == '\n')
				break;	/* newline is stored, like fgets() */
		} else if (rc == 0) {
			*ptr = 0;
			return(n - 1);	/* EOF, n - 1 bytes were read */
		} else
			return(-1);		/* error, errno set by read() */
	}

	*ptr = 0;	/* null terminate like fgets() */
	return(n);
}

ssize_t ReadLine::readlinebuf(void **vptrptr){
	if (read_cnt)
		*vptrptr = read_ptr;
	return(read_cnt);
}


ssize_t ReadLine::readLineEH(int fd, void *ptr, size_t maxlen){
	ssize_t		n;

	if ( (n = readline(fd, ptr, maxlen)) < 0){
		Error::sysTerminate("readline error");
	}
	
	return(n);	
}


