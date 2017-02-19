CC=g++
CFLAGS= -c -Wall 
LIBS= -lglut -lGL -lGLU -pthread -std=gnu++11 -Wl,--no-as-needed -lSDL2 -lSDL 

all: SuicidalLollipop

SuicidalLollipop:  main.o GLfunc.o Error.o Mouse.o Camera.o
	$(CC) main.o GLfunc.o Error.o Mouse.o Camera.o -o SuicidalLollipop $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

error.o: Error.cpp
	$(CC) $(CFLAGS) Error.cpp

GLfunc.o: GLfunc.cpp
	$(CC) $(CFLAGS) GLfunc.cpp

Mouse.o: Mouse.cpp
	$(CC) $(CFLAGS) Mouse.cpp

Camera.o: Camera.cpp
	$(CC) $(CFLAGS) Camera.cpp

clean:
	rm -rf *.o
