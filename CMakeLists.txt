cmake_minimum_required(VERSION 3.2)
project(asd CXX)

file(GLOB
    SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
)