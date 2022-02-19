cmake_minimum_required(VERSION 3.2)
project(klib-executable CXX)

add_subdirectory(lib)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
    klib
)
target_include_directories(${PROJECT_NAME}
    PUBLIC ./lib/
)