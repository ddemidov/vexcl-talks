cmake_minimum_required(VERSION 2.8)
project(abrau2013)
include(UseLATEX.cmake)

set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610")
set(USE_PGFPAGES "")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/vexcl_abrau2013.tex
    ${CMAKE_CURRENT_BINARY_DIR}/vexcl_abrau2013_slides.tex
    )

set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610,handout,notes=show")
set(USE_PGFPAGES "\\usepackage{pgfpages} \\pgfpagesuselayout{2 on 1}[a4paper,border shrink=5mm]")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/vexcl_abrau2013.tex
    ${CMAKE_CURRENT_BINARY_DIR}/vexcl_abrau2013_notes.tex
    )

add_latex_document(
    vexcl_abrau2013_slides.tex
    DEPENDS beamerthemeTorino.sty
            beamercolorthemechameleon.sty
            beamerouterthemedecolines.sty
            beamerinnerthemefancy.sty
    IMAGES tesla.png radeon.png intel.png forkme.png
           perfcmp-1.eps perfcmp-2.eps perfcmp-3.eps perfcmp-4.eps
           perfcmp-5.eps lorenz.eps
    DEFAULT_PDF MANGLE_TARGET_NAMES)

option(OUTPUT_NOTES "Create notes" OFF)

if (OUTPUT_NOTES)
    add_latex_document(
        vexcl_abrau2013_notes.tex
        DEPENDS beamerthemeTorino.sty
                beamercolorthemechameleon.sty
                beamerouterthemedecolines.sty
                beamerinnerthemefancy.sty
        IMAGES tesla.png radeon.png intel.png forkme.png
               perfcmp-1.eps perfcmp-2.eps perfcmp-3.eps perfcmp-4.eps
               perfcmp-5.eps lorenz.eps
        DEFAULT_PDF MANGLE_TARGET_NAMES)
endif (OUTPUT_NOTES)
