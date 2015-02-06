ROOT_DIR=../

include ${ROOT_DIR}/Make.defines

PROGS =checkopts.x

all: ${PROGS}

checkopts.x : checkopts.o
	$(CC) $(CFLAGS) $(LDFLAGS) checkopts.o ${LIBS}  -o $@
	
clean:
	\rm -rf ${CLEANFILES} $(PROGS)

