ROOT_DIR=../

include ${ROOT_DIR}/Make.defines

PROGS =StrcliSelect01.x

all: ${PROGS}

StrcliSelect01.x : StrcliSelect01.o
	$(CC) $(CFLAGS) $(LDFLAGS) StrcliSelect01.o ${LIBS}  -o $@

clean:
	\rm -rf ${CLEANFILES} $(PROGS)

