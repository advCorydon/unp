ROOT_DIR=../

include ${ROOT_DIR}/Make.defines

PROGS = client.x server.x server1.x

all: ${PROGS}

client.x : client.o
	$(CC) $(CFLAGS) $(LDFLAGS) client.o ${LIBS}  -o $@

server.x : server.o
	$(CC) $(CFLAGS) $(LDFLAGS) server.o ${LIBS}  -o $@
	
server1.x : server1.o
	$(CC) $(CFLAGS) $(LDFLAGS) server1.o ${LIBS}  -o $@

clean:
	\rm -rf ${CLEANFILES} $(PROGS)

