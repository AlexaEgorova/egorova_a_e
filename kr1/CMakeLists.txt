cmake_minimum_required(VERSION 3.0)

project(kr1)

set (CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(
	src
	${OpenCV_INCLUDE_DIRS})

set( SOURCES  
	src/source.cpp
)

add_executable( kr1 ${SOURCES} )

target_link_libraries(kr1 ${OpenCV_LIBS})