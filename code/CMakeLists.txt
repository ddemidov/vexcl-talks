foreach(src hello-opencl.cpp hello-vexcl.cpp)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${src}
        ${CMAKE_CURRENT_BINARY_DIR}/${src}
        COPYONLY
        )
endforeach()
