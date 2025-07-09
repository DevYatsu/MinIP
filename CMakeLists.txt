cmake_minimum_required(VERSION 3.10..)

project(MinIP C)

set(CMAKE_C_STANDARD 99)

add_executable(MinIP src/main.c src/ip.c src/ip.h src/arp.h)

