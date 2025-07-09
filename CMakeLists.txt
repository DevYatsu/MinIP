# https://stackoverflow.com/questions/41337060/how-can-i-tell-which-minimum-cmake-version-to-require-in-cmakelists-txt
# for understanding cmake version choice
cmake_minimum_required(VERSION 2.8.10)

project(MinIP C)

set(CMAKE_C_STANDARD 99)

add_executable(MinIP src/main.c)

