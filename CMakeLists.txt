cmake_minimum_required(VERSION 3.15)
project(vdfs C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -O0 -pedantic")

include_directories(src)

add_executable(vdfs src/main.c)

# target_link_libraries(vdfs fuse3)
