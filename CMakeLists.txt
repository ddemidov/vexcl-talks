cmake_minimum_required(VERSION 2.8)
project(delft)
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
        ${CMAKE_BINARY_DIR}/perf.pdf
    COMMAND
        ${CMAKE_CURRENT_SOURCE_DIR}/make_plots.py ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/make_plots.py
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
                    ${CMAKE_BINARY_DIR}/perf.pdf
            IMAGES tesla.png radeon.png intel.png compiling.png tudelft.png
            DEFAULT_PDF MANGLE_TARGET_NAMES)
    endfunction()

    add_document(${BEAMER_FILE} slides)
    if (OUTPUT_NOTES)
        set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610,handout,notes=show")
        set(USE_PGFPAGES "\\usepackage{pgfpages} \\pgfpagesuselayout{2 on 1}[a4paper,border shrink=5mm]")

        add_document(${BEAMER_FILE} notes)
    endif ()
endfunction()

add_slides(vexcl-delft-2017)

add_subdirectory(code)
