ROOT_DIR=../

include ${ROOT_DIR}/Make.defines

PROGS = tcpserver01.x tcpclient01.x

all: ${PROGS}

tcpclient01.x : tcpclient01.o
	$(CC) $(CFLAGS) $(LDFLAGS) tcpclient01.o ${LIBS}  -o $@

tcpserver01.x : tcpserver01.o
	$(CC) $(CFLAGS) $(LDFLAGS) tcpserver01.o ${LIBS}  -o $@
	

clean:
	\rm -rf ${CLEANFILES} $(PROGS)

