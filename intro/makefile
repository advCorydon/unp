include ../Make.defines

CFLAGS=-std=c++11 -g -Wall -pthread -std=gnu++11
#CFLAGS=-std=c++11 -g -Wall -pthread  -O0
#CFLAGS=-std=c++11 -g -Wall -pthread -gstabs+ -O0
#CFLAGS=-std=c++11 -g -Wall -pthread -ggdb -O0
LDFLAGS=-L/usr/local/gcc4.8.2/lib64 -lstdc++ -L/usr/local/gmp4.3.2/lib -L/usr/local/mpfr2.4.2/lib

SOURCES=main.cc 

OBJECTS=$(SOURCES:.cc=.o)

EXECUTABLE=test

all: $(EXECUTABLE)

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@
  
#$(OBJECTS):%.cc
.cc.o:
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	\rm -rf *.o $(EXECUTABLE) core.* 

