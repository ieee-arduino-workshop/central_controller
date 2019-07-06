CC=g++
FLAGS=-Wall -pedantic
SOURCES=central_controller.cpp Ball.cpp Player.cpp GameManager.cpp direction.h
HEADERS=direction.h controller_packet.h Ball.h Player.h GameManager.h
OBJECTS=central_controller.o Ball.o Player.o GameManager.o
BINARY=central_controller_debug

%.o: $(SOURCES) $(HEADERS)
	$(CC) $(FLAGS) -D DEBUG -c -o $@ $<

all:
	$(CC) $(FLAGS) -D DEBUG $(SOURCES) -o $(BINARY)

# Linux only!
clean:
	rm $(BINARY) $(OBJECTS)
