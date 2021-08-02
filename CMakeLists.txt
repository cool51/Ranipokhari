cmake_minimum_required(VERSION 3.17)
project(RaniPokhari)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES glad.c main.cpp)
set(OpenGlLinkers GLEW libGLEW.so -lglut -lglfw -lGLU -lGL -ldl X11 Xrandr pthread -lassimp)
link_directories(./)

add_executable(RaniPokhari glad.c main.cpp shader_s.h Mesh.h Mesh.cpp Model.h Camera.h shader_m.h RaniPokhari.h RaniPok.h)
target_link_libraries(RaniPokhari ${OpenGlLinkers})