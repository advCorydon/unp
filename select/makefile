ROOT_DIR=../

include ${ROOT_DIR}/Make.defines

PROGS =StrcliSelect01.x StrcliSelect02.x tcpserverselect01.x

all: ${PROGS}

StrcliSelect01.x : StrcliSelect01.o
	$(CC) $(CFLAGS) $(LDFLAGS) StrcliSelect01.o ${LIBS}  -o $@
	
StrcliSelect02.x : StrcliSelect02.o
	$(CC) $(CFLAGS) $(LDFLAGS) StrcliSelect02.o ${LIBS}  -o $@

tcpserverselect01.x : tcpserverselect01.o
	$(CC) $(CFLAGS) $(LDFLAGS) tcpserverselect01.o ${LIBS}  -o $@
	
clean:
	\rm -rf ${CLEANFILES} $(PROGS)

