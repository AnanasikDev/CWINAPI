cmake_minimum_required(VERSION 3.31)
project(uiapp C)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_executable(uiapp
    src/main.c
    src/ui.c
    src/graphics.c
    src/input.c
)
target_link_libraries(uiapp PRIVATE Comctl32)