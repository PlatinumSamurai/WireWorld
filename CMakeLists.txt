cmake_minimum_required(VERSION 3.15)
project(WireWorld)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(WireWorld WIN32 main.cpp field.hpp)

set(SFML_DIR "PATH_TO_SMFL_DIRECTORY_ON_YOUR_COMPUTER\\sfml\\GCC 7.3.0 MinGW (SEH) - 64-bit\\SFML-2.5.1\\lib\\cmake\\SFML")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

target_link_libraries(WireWorld sfml-graphics)