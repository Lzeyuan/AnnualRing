cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME "LuaBindCppTest")

add_executable(
    ${TARGET_NAME}
    main.cpp
)

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    lua
    dl
)

# 安装项目
install(
    TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin
)

file(GLOB LUA_FILES "${CMAKE_SOURCE_DIR}/service/*.lua")
install(
    FILES ${LUA_FILES}
    DESTINATION ${CMAKE_SOURCE_DIR}/bin
)