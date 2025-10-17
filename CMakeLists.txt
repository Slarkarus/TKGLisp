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

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(${PROJECT_NAME}.out ${SOURCES})

target_include_directories(${PROJECT_NAME}.out PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}.out PRIVATE magic_enum::magic_enum)
