CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=prog.c fonctions.c list.c

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=prog.out

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf *.o prog
