cmake_minimum_required(VERSION 2.8)
project(ysc-2012)
include(UseLATEX.cmake)

set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610")
set(USE_PGFPAGES "")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/mcpp_vexcl_2012.tex
    ${CMAKE_CURRENT_BINARY_DIR}/mcpp_vexcl_2012_slides.tex
    )

set(BEAMER_OPTIONS "compress,unicode,aspectratio=1610,handout,notes=show")
set(USE_PGFPAGES "\\usepackage{pgfpages} \\pgfpagesuselayout{2 on 1}[a4paper,border shrink=5mm]")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/mcpp_vexcl_2012.tex
    ${CMAKE_CURRENT_BINARY_DIR}/mcpp_vexcl_2012_notes.tex
    )

add_latex_document(
    mcpp_vexcl_2012_slides.tex
    IMAGES tesla.png radeon.png intel.png
	   lorenz.eps perfcmp.eps scaling.eps
	   oktobercat.jpg
    DEFAULT_PDF MANGLE_TARGET_NAMES)

add_latex_document(
    mcpp_vexcl_2012_notes.tex
    IMAGES tesla.png radeon.png intel.png
	   lorenz.eps perfcmp.eps scaling.eps
	   oktobercat.jpg
    DEFAULT_PDF MANGLE_TARGET_NAMES)

