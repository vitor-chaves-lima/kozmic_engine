if (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Android")
    message(FATAL_ERROR "The platform ${CMAKE_SYSTEM_NAME} is not supported!")
else ()
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(KOZMIC_PLATFORM "win32")
    endif ()

    message(STATUS "Platform: ${KOZMIC_PLATFORM}")
endif ()