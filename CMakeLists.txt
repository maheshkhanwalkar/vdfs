cmake_minimum_required(VERSION 3.15)
project(vdfs C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -O0")

include_directories(src)

add_executable(vdfs src/main.c src/disk/handler.c src/disk/handler.h
        src/defs.c src/defs.h src/disk/raw.c src/disk/raw.h src/part/mbr.c src/part/mbr.h)

# target_link_libraries(vdfs fuse3)
