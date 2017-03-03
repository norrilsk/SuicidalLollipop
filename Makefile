CC=g++
CFLAGS= -c -Wall -std=gnu++11
LIBS= -lglut -lGL -lGLU -pthread -Wl,--no-as-needed -lSDL2 -lSDL 

all: SuicidalLollipop

SuicidalLollipop:  main.o GLfunc.o Error.o Mouse.o Camera.o
	$(CC) main.o GLfunc.o Error.o Mouse.o Camera.o -o SuicidalLollipop $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

error.o: Error.cpp Error.hpp
	$(CC) $(CFLAGS) Error.cpp

GLfunc.o: GLfunc.cpp GLfunc.hpp Error.hpp Camera.hpp Mouse.hpp
	$(CC) $(CFLAGS) GLfunc.cpp

Mouse.o: Mouse.cpp Mouse.hpp
	$(CC) $(CFLAGS) Mouse.cpp

Camera.o: Camera.cpp Camera.hpp
	$(CC) $(CFLAGS) Camera.cpp

clean:
	rm -rf *.o
