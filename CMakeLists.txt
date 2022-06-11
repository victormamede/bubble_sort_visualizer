cmake_minimum_required(VERSION 3.22)

project(Sorter)

find_package(SDL2 REQUIRED)

set(SOURCE_DIR src)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(sorter
               ${SOURCE_DIR}/main.c
               ${SOURCE_DIR}/draw_values.c
               ${SOURCE_DIR}/bubble_sort.c
)

target_link_libraries(sorter ${SDL2_LIBRARIES})