cmake_minimum_required(VERSION 3.8)
project(hw4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp Curve.cpp Curve.h Pointf.cpp Pointf.h CurveManager.cpp CurveManager.h Mode.h)
add_executable(hw4 ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )

target_link_libraries(hw4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})