cmake_minimum_required(VERSION 3.19)
project(lr7)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(lr7 main.cpp cmake-build-debug figures.h)

target_link_libraries(lr7 sfml-graphics sfml-audio)