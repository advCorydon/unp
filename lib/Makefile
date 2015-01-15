include ../Make.defines

SRCS=error.cc 

OBJS=$(SRCS:.cc=.o)

LIBUNP_NAME = ../libunp.a

all:    ${OBJS}
	ar rv ${LIBUNP_NAME} $?
	${RANLIB} ${LIBUNP_NAME}

clean:
	\rm -rf ${CLEANFILES} ${LIBUNP_NAME}