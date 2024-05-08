cmake_minimum_required(VERSION 3.10)
project(.)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pthread -DGL_SILENCE_DEPRECATION")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(mandel mandelbrot.c)
target_include_directories(mandel PRIVATE ${GLUT_INCLUDE_DIRS})
target_link_libraries(mandel ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)
