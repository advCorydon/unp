#ifndef UNIX_WRAPPER_H__
#define UNIX_WRAPPER_H__

class UnixWrapper{
public:
	static void write(int fd, const void *ptr, ssize_t nbytes);
	static ssize_t read(int fd, void* ptr, size_t nbytes);
	static void close(int fd);
};

#endif
