project(sld2bnd)

cmake_minimum_required(VERSION 2.6)

find_package(BISON REQUIRED)

bison_target(MyParser io/gram.sldbnd.y ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c)

add_definitions("-DPROTOTYPE")

file(GLOB src_io "io/*.c")
file(GLOB src_surface "surface/*.c")
file(GLOB src_stack "stack/*.c")
file(GLOB src_arit "arit/*.c")
file(GLOB inc "include/*.h")

include_directories(include ${CMAKE_CURRENT_BINARY_DIR})

set(LIBRARY_NAME "mylib")
add_library(${LIBRARY_NAME} STATIC ${inc} ${src_io} ${src_surface} ${src_stack} ${src_arit} ${BISON_MyParser_OUTPUTS})

add_executable(sld2bnd sld2bnd.c)
target_link_libraries(sld2bnd ${LIBRARY_NAME} m)
