set(examples hello-opencl hello-vexcl lorenz-naive pi)

find_package(Boost COMPONENTS system filesystem)
find_package(OpenCL REQUIRED)
set(VEXCL_ROOT $ENV{VEXCL_ROOT} CACHE STRING "VexCL root")

include_directories(
    ${VEXCL_ROOT}
    ${Boost_INCLUDE_DIRS}
    ${OPENCL_INCLUDE_DIRS}
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-ignored-attributes")

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
    target_link_libraries(${f} ${OpenCL_LIBRARY} ${Boost_LIBRARIES})
endforeach()

add_subdirectory(pybind11)
pybind11_add_module(pylorenz pylorenz.cpp)
target_link_libraries(pylorenz PRIVATE ${OpenCL_LIBRARY} ${Boost_LIBRARIES})
