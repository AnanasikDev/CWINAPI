cmake_minimum_required(VERSION 3.14)
project(uiapp C)

set(ZLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include/zlib-1.3.1")
#set(ZLIB_ROOT, "C:/Archive/Code/C/GUIApp/include/zlib")
#set(ZLIB_INCLUDE_DIR, "C:/Archive/Code/C/GUIApp/include/zlib")

add_subdirectory(include/zlib)
add_subdirectory(include/libpng)

add_executable(uiapp
    src/main.c
    src/ui.c
    src/graphics.c
    src/input.c
)

#target_link_libraries(uiapp zlib)
target_link_libraries(uiapp PRIVATE libpng)