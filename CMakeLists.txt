cmake_minimum_required(VERSION 3.10)

project(deamon)

set(SOURCES
	./source/main.c
	./source/deamon.c
)

add_executable(deamon ${SOURCES})
