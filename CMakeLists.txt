cmake_minimum_required(VERSION 2.8)

project(cterp)

add_executable(cterp pc.c)

install(TARGETS cterp DESTINATION bin)