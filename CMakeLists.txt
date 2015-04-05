cmake_minimum_required(VERSION 3.0)
project(sound_process_base)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

set(SOURCE_FILES main.cpp)
add_executable(sound_process_base ${SOURCE_FILES} PhaseSpaceAnalyser.cpp PhaseSpaceAnalyser.h analyser.h WavFileHander.cpp WavFileHander.h Base_Plotter.h ToFilePlotter.cpp ToFilePlotter.h GnuplotPlotter.cpp GnuplotPlotter.h CombFilterAnalyser.cpp CombFilterAnalyser.h WaveFunction.h CombFunction.cpp CombFunction.h)

target_link_libraries(sound_process_base sndfile)