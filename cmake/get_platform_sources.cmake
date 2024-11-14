function(get_platform_sources platform result)
    file(GLOB files "${CMAKE_SOURCE_DIR}/lib/src/platform/${platform}/*")
    set(${result} ${files} PARENT_SCOPE)
endfunction()
