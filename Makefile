CC=g++
CFLAGS= -c -Wall -std=gnu++11 -O2
LIBS= -lglut -lGL -lGLU -lSDL2 -lSDL -lGLEW

all: SuicidalLollipop

SuicidalLollipop:  main.o GLfunc.o Error.o Mouse.o Keyboard.o Camera.o Object3D.o MovableObject.o Player.o NPC.o MashObject.o Shaders.o Loger.o Room.o Game.o 
	$(CC) main.o GLfunc.o Error.o Mouse.o Keyboard.o Camera.o Object3D.o MovableObject.o Player.o Game.o NPC.o MashObject.o Shaders.o Loger.o Room.o -o SuicidalLollipop $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Error.o: Error.cpp Error.hpp
	$(CC) $(CFLAGS) Error.cpp

GLfunc.o: GLfunc.cpp GLfunc.hpp Error.hpp Camera.hpp Mouse.hpp
	$(CC) $(CFLAGS) GLfunc.cpp

Mouse.o: Mouse.cpp Mouse.hpp
	$(CC) $(CFLAGS) Mouse.cpp

Camera.o: Camera.cpp Camera.hpp
	$(CC) $(CFLAGS) Camera.cpp

Loger.o: Loger.cpp Loger.hpp
	$(CC) $(CFLAGS) Loger.cpp
	
Keyboard.o: Keyboard.cpp Keyboard.hpp
	$(CC) $(CFLAGS) Keyboard.cpp

Object3D.o: Objects/Object3D.cpp Objects/Object3D.hpp
	$(CC) $(CFLAGS) Objects/Object3D.cpp

MovableObject.o: Objects/MovableObject.cpp Objects/MovableObject.hpp
	$(CC) $(CFLAGS) Objects/MovableObject.cpp
	
Player.o: Objects/Player.cpp Objects/Player.hpp
	$(CC) $(CFLAGS) Objects/Player.cpp

NPC.o: Objects/NPC.cpp Objects/NPC.hpp
	$(CC) $(CFLAGS) Objects/NPC.cpp
	
MashObject.o: Objects/MashObject.cpp Objects/MashObject.hpp
	$(CC) $(CFLAGS) Objects/MashObject.cpp

Room.o: Objects/Room.cpp Objects/Room.hpp
	$(CC) $(CFLAGS) Objects/Room.cpp
	
Shaders.o: Shaders.cpp Shaders.hpp
	$(CC) $(CFLAGS) Shaders.cpp

Game.o: Game.cpp Game.hpp Objects/Objects.hpp
	$(CC) $(CFLAGS) Game.cpp
	
clean:
	rm -rf *.o
