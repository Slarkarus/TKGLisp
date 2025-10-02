cmake_minimum_required(VERSION 3.0)
project(TKGLisp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME}.out ${SOURCES})

target_include_directories(${PROJECT_NAME}.out PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
