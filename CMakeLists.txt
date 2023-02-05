cmake_minimum_required(VERSION 3.24)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror ")
include_directories(SYSTEM ./)

add_executable(ft_containers Garbage/main.cpp Unit_test/utility_test.cpp Unit_test/type_traits_test.cpp Unit_test/stack_test.cpp Unit_test/Unit_test.hpp)
