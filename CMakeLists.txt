cmake_minimum_required(VERSION 3.1)

project(Enigma VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} encryptor.cpp main.cpp)
