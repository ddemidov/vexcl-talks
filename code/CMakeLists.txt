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

foreach(f ${examples})
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${f}.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/${f}.cpp
        COPYONLY
        )

    add_executable(${f} ${f}.cpp)
    target_link_libraries(${f} ${OpenCL_LIBRARY} ${Boost_LIBRARIES})
endforeach()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/pi-kernel.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/pi-kernel.cpp
    COPYONLY
    )
