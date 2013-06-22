cmake_minimum_required(VERSION 2.8)
project(json)

include_directories(include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src JSON_SOURCES)

add_library(json STATIC ${JSON_SOURCES})
add_library(libjson SHARED ${JSON_SOURCES})
