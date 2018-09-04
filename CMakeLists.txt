cmake_minimum_required(VERSION 2.8)

# *********************** Required *************************
project(test)
set(TARGET kiev_test)
# **********************************************************

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -O3 -std=c++0x -Wall -Werror")

add_executable(socket_client src/socket_client.cpp)
target_link_libraries(socket_client -lsnappy -luuid -pthread -lssl -lcrypto -lz -ldl -static)

add_executable(socket_server src/socket_server.cpp)
target_link_libraries(socket_client -lsnappy -luuid -pthread -lssl -lcrypto -lz -ldl -static)
