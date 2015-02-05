ROOT_DIR=../

include ${ROOT_DIR}/Make.defines

PROGS = tcpserver01.x tcpclient01.x tcpclient04.x tcpserver04.x

all: ${PROGS}

tcpclient01.x : tcpclient01.o
	$(CC) $(CFLAGS) $(LDFLAGS) tcpclient01.o ${LIBS}  -o $@

tcpclient04.x : tcpclient04.o
	$(CC) $(CFLAGS) $(LDFLAGS) tcpclient04.o ${LIBS}  -o $@

tcpserver01.x : tcpserver01.o
	$(CC) $(CFLAGS) $(LDFLAGS) tcpserver01.o ${LIBS}  -o $@
	
tcpserver04.x : tcpserver04.o
	$(CC) $(CFLAGS) $(LDFLAGS) tcpserver04.o ${LIBS}  -o $@

clean:
	\rm -rf ${CLEANFILES} $(PROGS)

