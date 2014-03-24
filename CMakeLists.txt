# This file is part of rscript.
# rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

cmake_minimum_required(VERSION 2.8)
project(RSCRIPT)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INSTALL_PREFIX "")

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -pedantic") 

file(GLOB_RECURSE SOURCES "src/*.cc" "src/*.hpp" "include/*.hpp")

include_directories(${CMAKE_SOURCE_DIR})

add_library(rscript ${SOURCES})
target_link_libraries(rscript pthread)

add_subdirectory(driver)
