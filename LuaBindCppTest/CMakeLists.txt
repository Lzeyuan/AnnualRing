cmake_minimum_required(VERSION 3.25)

project(QuickStart VERSION 1.0 LANGUAGES C CXX)


add_subdirectory(src)

message("Test set scope")
message("TARGET_NAME: ${TARGET_NAME}")
message(EXECUTABLE_OUTPUT_PATH: ${EXECUTABLE_OUTPUT_PATH})
message(LUA_PATH: ${LUA_PATH})