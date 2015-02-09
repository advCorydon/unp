ROOT_DIR=../

include ${ROOT_DIR}/Make.defines

PROGS =hostent.x 

all: ${PROGS}

hostent.x : hostent.o
	$(CC) $(CFLAGS) $(LDFLAGS) hostent.o ${LIBS}  -o $@
	
clean:
	\rm -rf ${CLEANFILES} $(PROGS)

