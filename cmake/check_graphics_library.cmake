function(check_graphics_libraries_available libraries_list)
    find_package(OpenGL REQUIRED)

    set(libraries "")

    if (OPENGL_FOUND)
        list(APPEND libraries "ogl")
    endif ()

    set(${libraries_list} ${libraries} PARENT_SCOPE)
endfunction()