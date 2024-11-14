cmake_minimum_required(VERSION 3.29)
project(kozmic)

set(CMAKE_CXX_STANDARD 20)

include("${CMAKE_SOURCE_DIR}/cmake/check_unicode_support.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/target_definitions.cmake")

add_subdirectory(sandbox)
