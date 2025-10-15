cmake_minimum_required(VERSION 3.0)
project(TKGLisp)

include(FetchContent)
FetchContent_Declare(
    magic_enum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
    GIT_TAG v0.9.5 
)
FetchContent_MakeAvailable(magic_enum)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
message(STATUS "Sources: ${SOURCES}")


add_executable(${PROJECT_NAME}.out ${SOURCES})

target_include_directories(${PROJECT_NAME}.out PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}.out PRIVATE magic_enum::magic_enum)
