cmake_minimum_required(VERSION 3.16)
project(QOI-Format-Codec)

set(CMAKE_CXX_STANDARD 17)

add_executable(conv main.cpp)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/")
install(TARGETS conv RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
