cmake_minimum_required(VERSION 3.1)

project(Enigma VERSION 1.0)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

#set(SOURCE_FILES main.cpp)

add_executable(enigma ${SOURCE_FILES} encryptor.cpp main.cpp)
target_include_directories(enigma
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/.
)
