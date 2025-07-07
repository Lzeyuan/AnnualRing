cmake_minimum_required(VERSION 3.25)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(QuickStart VERSION 1.0 LANGUAGES C CXX)

add_subdirectory(3rd/lua)
add_subdirectory(src)
