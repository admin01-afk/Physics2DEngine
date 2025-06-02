cmake_minimum_required(VERSION 3.10)
project(Physics2DEngine)

set(CMAKE_CXX_STANDARD 17)


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} include)

file(GLOB SOURCES src/*.cpp)

add_executable(Physics2DEngine ${SOURCES})
target_link_libraries(Physics2DEngine ${SDL2_LIBRARIES})