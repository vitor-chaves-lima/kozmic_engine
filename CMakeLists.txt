cmake_minimum_required(VERSION 3.29)
project(kozmic)

set(CMAKE_CXX_STANDARD 20)

include("cmake/check_unicode_support.cmake")

add_subdirectory(sandbox)
