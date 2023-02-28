cmake_minimum_required(VERSION 3.23.2)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS #[["-Wall -Wextra -Werror "]])
include_directories(SYSTEM ./)

add_executable(ft_containers test/sources/vector_tests/constructor.cpp )
