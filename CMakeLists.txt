project(CartographyML)

cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

########################
## Enable C++11 and all warnings

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

########################
## Find GDAL

find_package(GDAL REQUIRED

include_directories(${GDAL_INCLUDE_DIR} )
)

########################
## Find Mapnik

find_package(Mapnik REQUIRED)
add_definitions(${MAPNIK_DEFINITIONS})

########################
## Find Qt5

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Positioning REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt53DRender)
find_package(Qt53DQuickExtras) # TODO remove

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Quick_INCLUDE_DIRS}) # Make KDevelop 4 happy, TODO remove later

########################
## Generate config.h
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

########################
## subdirectories

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(GeometryML)
add_subdirectory(MapnikML)
add_subdirectory(CartographerML)
add_subdirectory(TerrainML)
if(Qt53DRender_FOUND)
  add_subdirectory(TerrainML3D)
endif()
add_subdirectory(examples)
