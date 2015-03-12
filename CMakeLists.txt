cmake_minimum_required(VERSION 3.0)
project(sound_process_base)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(sound_process_base ${SOURCE_FILES})

target_link_libraries(sound_process_base sndfile)