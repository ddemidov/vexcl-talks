cmake_minimum_required(VERSION 2.8)
project(changchun)
include(UseLATEX.cmake)

set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610")
set(USE_PGFPAGES "")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/vexcl_changchun.tex
    ${CMAKE_CURRENT_BINARY_DIR}/vexcl_changchun_slides.tex
    )

set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610,handout,notes=show")
set(USE_PGFPAGES "\\usepackage{pgfpages} \\pgfpagesuselayout{2 on 1}[a4paper,border shrink=5mm]")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/vexcl_changchun.tex
    ${CMAKE_CURRENT_BINARY_DIR}/vexcl_changchun_notes.tex
    )

add_latex_document(
    vexcl_changchun_slides.tex
    DEPENDS beamerthemeTorino.sty
            beamercolorthemechameleon.sty
            beamerouterthemedecolines.sty
            beamerinnerthemefancy.sty
    IMAGES tesla.png radeon.png intel.png
	   lorenz.eps perfnaive.eps perfgen.eps
	   forkme.png
    DEFAULT_PDF MANGLE_TARGET_NAMES)

option(OUTPUT_NOTES "Create notes" OFF)

if (OUTPUT_NOTES)
    add_latex_document(
        vexcl_changchun_notes.tex
        DEPENDS beamerthemeTorino.sty
                beamercolorthemechameleon.sty
                beamerouterthemedecolines.sty
                beamerinnerthemefancy.sty
        IMAGES tesla.png radeon.png intel.png
               lorenz.eps perfnaive.eps perfgen.eps
               forkme.png
        DEFAULT_PDF MANGLE_TARGET_NAMES)
endif (OUTPUT_NOTES)
