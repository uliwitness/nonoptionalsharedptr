cmake_minimum_required(VERSION 3.24)
project(nonoptionalsharedptr)

set(CMAKE_CXX_STANDARD 23)

add_executable(nonoptionalsharedptr main.cpp nonoptional_shared_ptr.hpp optional_shared_ptr.hpp)
