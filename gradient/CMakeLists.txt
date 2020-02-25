cmake_minimum_required(VERSION 3.0)

project(gradient)

set (CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(
	src
	${OpenCV_INCLUDE_DIRS})

set( SOURCES  
	src/source.cpp
)

add_executable( gradient ${SOURCES} )

target_link_libraries(gradient ${OpenCV_LIBS})