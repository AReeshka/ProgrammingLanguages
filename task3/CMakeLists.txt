cmake_minimum_required(VERSION 3.7)
project(task3)

set(CMAKE_CXX_STANDARD 11)

add_library(rational rational.cpp rational.h)
install (TARGETS rational DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (FILES rational.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
