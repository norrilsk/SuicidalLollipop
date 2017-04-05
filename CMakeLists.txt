cmake_minimum_required(VERSION 3.6)
project(SuicidalLollipop)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL  REQUIRED)
include_directories($(OPENGL_INCLUDE_DIRS))
link_libraries(${OPENGL_LIBRARIES})
find_package(GLEW  REQUIRED)
include_directories($(GLEW_INCLUDE_DIRS))
link_libraries(${GLEW_LIBRARIES})

set(SOURCE_FILES main.cpp GLfunc.hpp Error.cpp Error.hpp Game.cpp Game.hpp GLfunc.hpp GLfunc.cpp Keyboard.cpp Keyboard.hpp Loger.cpp Loger.hpp Mouse.cpp Mouse.hpp Shaders.cpp Shaders.hpp Camera.cpp Camera.hpp
        ./Objects/DrawableObject.hpp ./Objects/MashObject.cpp ./Objects/MashObject.hpp ./Objects/Menu.cpp ./Objects/Menu.hpp ./Objects/MovableObject.cpp ./Objects/MovableObject.hpp ./Objects/NPC.cpp ./Objects/NPC.hpp
        ./Objects/Object2D.cpp ./Objects/Object2D.hpp ./Objects/Object3D.cpp ./Objects/Object3D.hpp ./Objects/Objects.hpp ./Objects/Player.cpp ./Objects/Player.hpp ./Objects/Room.cpp ./Objects/Room.hpp
        ./Shaders/fragmentshader.glsl ./Shaders/vertexshader.glsl Storage.cpp Storage.hpp Texture.cpp Texture.hpp SDLTexture.cpp SDLTexture.hpp Objects/Model.cpp Objects/Model.hpp)

set(UTILITY_SOURCE_FILES utility.cpp Loger.cpp Loger.hpp  Error.cpp Error.hpp SDLTexture.cpp SDLTexture.hpp)

add_executable(SuicidalLollipop ${SOURCE_FILES})
add_executable(utility ${UTILITY_SOURCE_FILES} utility.cpp)
target_link_libraries(SuicidalLollipop SDL2 SDL2_image)
target_link_libraries(utility SDL2 SDL2_image)