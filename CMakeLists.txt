project(MapnikML)

cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

########################
## Enable C++11 and all warnings

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

########################
## Find Mapnik

find_package(Mapnik)

########################
## Find Qt5

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Positioning REQUIRED)
find_package(Qt5Quick REQUIRED)

########################
## subdirectories

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(MapnikML)
add_subdirectory(src)
add_subdirectory(examples)