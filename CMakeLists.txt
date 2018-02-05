cmake_minimum_required(VERSION 3.1)
project(toulouse)
include(UseLATEX.cmake)

#set(BEAMER_OPTIONS "compress,unicode,smaller,aspectratio=169")
set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610")
set(USE_PGFPAGES "")

option(OUTPUT_NOTES "Create notes" OFF)

function(mplfigure fname)
    add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/${fname}.pdf
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${fname}.py
                ${CMAKE_BINARY_DIR}/${fname}.pdf
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${fname}.py
                ${CMAKE_CURRENT_SOURCE_DIR}/chameleon.py
        )
endfunction()

mplfigure(mcpi)
mplfigure(lorenz)

add_custom_command(
    OUTPUT
        ${CMAKE_BINARY_DIR}/cpu_vs_gpu_1.pdf
        ${CMAKE_BINARY_DIR}/cpu_vs_gpu_2.pdf
    COMMAND
        ${CMAKE_CURRENT_SOURCE_DIR}/cpu_vs_gpu.py ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/cpu_vs_gpu.py
        ${CMAKE_CURRENT_SOURCE_DIR}/chameleon.py
    )

add_custom_command(
    OUTPUT
        ${CMAKE_BINARY_DIR}/backends.pdf
    COMMAND
        ${CMAKE_CURRENT_SOURCE_DIR}/backends.py ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/backends.py
        ${CMAKE_CURRENT_SOURCE_DIR}/chameleon.py
    )

function(add_slides BEAMER_FILE)
    function(add_document SOURCE SUFFIX)
        configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}.tex
            ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE}-${SUFFIX}.tex
            )

        add_latex_document(
            ${BEAMER_FILE}-${SUFFIX}.tex
            INPUTS  ribbon.tex
            DEPENDS beamerthemeTorino.sty
                    beamercolorthemechameleon.sty
                    beamerouterthemedecolines.sty
                    beamerinnerthemefancy.sty
                    ${CMAKE_BINARY_DIR}/mcpi.pdf
                    ${CMAKE_BINARY_DIR}/lorenz.pdf
                    ${CMAKE_BINARY_DIR}/cpu_vs_gpu_1.pdf
                    ${CMAKE_BINARY_DIR}/cpu_vs_gpu_2.pdf
                    ${CMAKE_BINARY_DIR}/backends.pdf
            IMAGES tesla.png radeon.png intel.png compiling.png lpt.pdf
            DEFAULT_PDF MANGLE_TARGET_NAMES)
    endfunction()

    add_document(${BEAMER_FILE} slides)
    if (OUTPUT_NOTES)
        set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610,handout,notes=show")
        set(USE_PGFPAGES "\\usepackage{pgfpages} \\pgfpagesuselayout{2 on 1}[a4paper,border shrink=5mm]")

        add_document(${BEAMER_FILE} notes)
    endif ()
endfunction()

add_slides(vexcl-toulouse-2018)

add_subdirectory(code)
