set(TARGET_NAME "lua")

add_library(
    ${TARGET_NAME}
    INTERFACE
)

# 添加lua库
target_include_directories(    
    ${TARGET_NAME}
    INTERFACE
    src
)

target_link_directories(
    ${TARGET_NAME}
    INTERFACE
    src
)

target_link_libraries(
    ${TARGET_NAME}
    INTERFACE
    liblua.a
)