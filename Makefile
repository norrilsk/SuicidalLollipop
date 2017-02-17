CC=g++
CFLAGS= -c -Wall 
LIBS= -lglut -lGL -lGLU -pthread -std=gnu++11 -Wl,--no-as-needed -lSDL2 -lSDL 

all: SuicidalLollipop

SuicidalLollipop:  main.o GLfunc.o error.o
	$(CC) main.o GLfunc.o error.o -o SuicidalLollipop $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

error.o: error.cpp
	$(CC) $(CFLAGS) error.cpp

GLfunc.o: GLfunc.cpp
	$(CC) $(CFLAGS) GLfunc.cpp

clean:
	rm -rf *.o
