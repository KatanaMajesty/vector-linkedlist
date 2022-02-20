cmake_minimum_required(VERSION 3.2)
project(klib CXX)

add_library(${PROJECT_NAME} klib.cpp kvec.cpp)
target_include_directories(${PROJECT_NAME}
    PRIVATE .
)