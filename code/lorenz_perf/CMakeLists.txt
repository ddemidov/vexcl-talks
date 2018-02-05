find_package(Boost COMPONENTS timer filesystem)

set(CUDA_TARGET_ARCH "Kepler" CACHE STRING "Target architecture(s) for CUDA")

cuda_add_executable(lorenz_thrust_cu lorenz_thrust.cu)
target_link_libraries(lorenz_thrust_cu Boost::timer Boost::filesystem)

cuda_add_executable(lorenz_thrust_omp lorenz_thrust.cu
    OPTIONS "-Xcompiler;-fopenmp;-DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP;-DCPU_RUN")
target_link_libraries(lorenz_thrust_omp Boost::timer Boost::filesystem -fopenmp)

vexcl_add_executables(lorenz_vexcl_naive lorenz_vexcl_naive.cpp)
target_link_libraries(lorenz_vexcl_naive INTERFACE Boost::timer Boost::filesystem)

vexcl_add_executables(lorenz_vexcl_symb lorenz_vexcl_symb.cpp)
target_link_libraries(lorenz_vexcl_symb INTERFACE Boost::timer Boost::filesystem)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/run_tests.sh
    ${CMAKE_CURRENT_BINARY_DIR}/run_tests.sh
    COPYONLY
    )

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/rename.sh
    ${CMAKE_CURRENT_BINARY_DIR}/rename.sh
    COPYONLY
    )
