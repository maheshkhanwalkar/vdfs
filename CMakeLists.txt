cmake_minimum_required(VERSION 3.15)
project(vdfs CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(vdfs src/main.cpp src/disk/handler.h src/disk/raw/raw_handler.cpp src/disk/raw/raw_handler.h
        src/disk/recognise.cpp src/disk/recognise.h)

target_link_libraries(vdfs fuse3)
