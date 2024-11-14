# CheckUnicodeSupport.cmake
#
# This module checks if Unicode support is available on the system and configures
# the necessary definitions and compiler flags to enable Unicode.
# It defines a variable UNICODE_AVAILABLE to indicate the Unicode support status.

include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)

set(KOZMIC_UNICODE_SUPPORT FALSE CACHE BOOL "Indicates if Unicode support is available")

if (MSVC)
    set(KOZMIC_UNICODE_SUPPORT TRUE)
    add_definitions(-DUNICODE -D_UNICODE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
    message(STATUS "Configuring for Unicode support with MSVC.")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    check_cxx_compiler_flag("-finput-charset=UTF-8" HAS_INPUT_CHARSET)
    check_cxx_compiler_flag("-fexec-charset=UTF-8" HAS_EXEC_CHARSET)

    if (HAS_INPUT_CHARSET AND HAS_EXEC_CHARSET)
        set(KOZMIC_UNICODE_SUPPORT TRUE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8 -fexec-charset=UTF-8")
        message(STATUS "Configuring for Unicode support with GCC/Clang.")
    else ()
        message(WARNING "Unicode support flags are not available on this GCC/Clang version.")
    endif ()
endif ()

if (NOT KOZMIC_UNICODE_SUPPORT)
    check_cxx_source_compiles("
        #include <string>
        int main() {
            std::wstring test = L\"Test Unicode\";
            return 0;
        }
    " HAS_UNICODE_SUPPORT)

    if (HAS_UNICODE_SUPPORT)
        set(KOZMIC_UNICODE_SUPPORT TRUE)
        message(STATUS "Unicode support verified with std::wstring test.")
    else ()
        message(WARNING "Unicode support could not be confirmed; std::wstring test failed.")
    endif ()
endif ()