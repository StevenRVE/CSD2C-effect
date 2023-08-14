cmake_minimum_required(VERSION 3.17)
project(CSD2C-effect VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories("C:/Program Files/JACK2/include")

# Add the path to the directory containing the .lib files
link_directories("C:/Program Files/JACK2/lib")

add_executable(d source/main.cpp source/distortion.cpp source/distortion.hpp source/jack_module.cpp source/jack_module.h source/oscillator.cpp source/oscillator.hpp)

# Link against the Jack2 library
target_link_libraries(d PRIVATE "C:/Program Files/JACK2/lib/libjack64.lib")
