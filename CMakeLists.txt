cmake_minimum_required(VERSION 3.11)

project(otc)

include_directories("./")
include_directories("./header")

aux_source_directory(./ MAIN_SOURCES)
aux_source_directory(./header HEADER_SOURCES)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(${PROJECT_NAME}  ${MAIN_SOURCES} ${HEADER_SOURCES})