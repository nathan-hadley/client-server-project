cmake_minimum_required(VERSION 3.19)
project(server)

set(CMAKE_CXX_STANDARD 11)

add_executable(server main.cpp RPCServer.cpp RPCImpl.cpp)

set(CMAKE_CXX_FLAGS -pthread)