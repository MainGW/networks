cmake_minimum_required(VERSION 3.17)
project(networks)

aux_source_directory(src PRO_SRCS)
include_directories(include)

set(CMAKE_CXX_STANDARD 20)

add_library(networks SHARED ${PRO_SRCS})