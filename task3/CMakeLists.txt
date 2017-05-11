cmake_minimum_required(VERSION 3.7)
project(task3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES rational.h rational.cpp)
add_executable(task3 ${SOURCE_FILES})
install (TARGETS rational DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (FILES rational.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install (FILES rational.cpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
