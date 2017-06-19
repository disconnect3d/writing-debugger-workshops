CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
LDFLAGS=

SOURCES=$(wildcard *.c )
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=exec

all: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS)
