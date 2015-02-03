ROOT_DIR=../..

include ${ROOT_DIR}/Make.defines

SOURCES=main.cc 

EXECUTABLE=test.x

all: $(EXECUTABLE)

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) ${LIBS}  -o $@
  
clean:
	\rm -rf ${CLEANFILES} $(EXECUTABLE)

