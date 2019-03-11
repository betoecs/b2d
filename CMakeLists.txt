project(b2d)
cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/b2d)

configure_file(${CMAKE_SOURCE_DIR}/doc/epic-doc.conf.cmake ${CMAKE_SOURCE_DIR}/doc/epic-doc.conf)