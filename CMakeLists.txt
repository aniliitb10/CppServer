cmake_minimum_required(VERSION 3.8)
project(CppServer)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES bin/my/Server/Server.cpp util/util.cpp)
add_executable(CppServer ${SOURCE_FILES})