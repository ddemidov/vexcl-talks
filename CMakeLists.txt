cmake_minimum_required(VERSION 2.8)
project(cse13)
include(UseLATEX.cmake)

set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610")
set(USE_PGFPAGES "")

option(OUTPUT_NOTES "Create notes" OFF)

function(add_slides BEAMER_FILE)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${BEAMER_FILE}.tex
        ${CMAKE_CURRENT_BINARY_DIR}/${BEAMER_FILE}_slides.tex
        )

    set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610,handout,notes=show")
    set(USE_PGFPAGES "\\usepackage{pgfpages} \\pgfpagesuselayout{2 on 1}[a4paper,border shrink=5mm]")

    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${BEAMER_FILE}.tex
        ${CMAKE_CURRENT_BINARY_DIR}/${BEAMER_FILE}_notes.tex
        )

    add_latex_document(
        ${BEAMER_FILE}_slides.tex
        DEPENDS beamerthemeTorino.sty
                beamercolorthemechameleon.sty
                beamerouterthemedecolines.sty
                beamerinnerthemefancy.sty
        IMAGES tesla.png radeon.png intel.png forkme.png
        DEFAULT_PDF MANGLE_TARGET_NAMES)

    if (OUTPUT_NOTES)
        add_latex_document(
            ${BEAMER_FILE}_notes.tex
            DEPENDS beamerthemeTorino.sty
                    beamercolorthemechameleon.sty
                    beamerouterthemedecolines.sty
                    beamerinnerthemefancy.sty
            IMAGES tesla.png radeon.png intel.png forkme.png
            DEFAULT_PDF MANGLE_TARGET_NAMES)
    endif ()
endfunction()

add_slides(vexcl_austin_part1)
add_slides(vexcl_austin_part2)
