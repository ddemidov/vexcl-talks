set(examples hello-opencl hello-vexcl lorenz-naive pi)

find_package(OpenMP)
find_package(VexCL)
find_package(CUDA)

foreach(f hello-opencl.cpp hello-vexcl.cpp lorenz.cpp pi.cpp pi-kernel.cpp
        pylorenz.cpp lorenz.ipynb)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${f}
        ${CMAKE_CURRENT_BINARY_DIR}/${f}
        COPYONLY
        )
endforeach()

foreach(f hello-opencl hello-vexcl lorenz pi)
    add_executable(${f} ${f}.cpp)
    target_link_libraries(${f} VexCL::OpenCL)
endforeach()

add_subdirectory(lorenz_perf)

add_subdirectory(pybind11)
pybind11_add_module(pylorenz pylorenz.cpp)
target_link_libraries(pylorenz PRIVATE VexCL::OpenCL)
