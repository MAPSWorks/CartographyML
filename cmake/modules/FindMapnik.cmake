# - Find Mapnik
# Find the native Mapnik includes and library
#
#   MAPNIK_FOUND        - True if MAPNIK found.
#   MAPNIK_INCLUDE_DIRS - where to find mapnik/map.hpp, etc.
#   MAPNIK_LIBRARIES    - List of libraries when using MAPNIK
#

find_path( MAPNIK_INCLUDE_DIR mapnik/map.hpp )

find_library( MAPNIK_LIBRARY
              NAMES mapnik2 mapnik )

find_program(MAPNIK_CONFIG NAMES mapnik-config
  PATHS /usr/bin
        /usr/local/bin
        /opt/local/bin)
              
              
# handle the QUIETLY and REQUIRED arguments and set MAPNIK_FOUND to TRUE if
# all listed variables are TRUE
include( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( Mapnik DEFAULT_MSG MAPNIK_LIBRARY MAPNIK_INCLUDE_DIR MAPNIK_CONFIG)

mark_as_advanced( MAPNIK_INCLUDE_DIR MAPNIK_LIBRARY )

if(MAPNIK_FOUND)
  set(MAPNIK_INCLUDE_DIRS ${MAPNIK_INCLUDE_DIR})
  set(MAPNIK_LIBRARIES ${MAPNIK_LIBRARY})
  
  execute_process(COMMAND mapnik-config --input-plugins OUTPUT_VARIABLE MAPNIK_INPUT_PLUGINS_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND mapnik-config --defines OUTPUT_VARIABLE MAPNIK_DEFINITIONS OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
  set(MAPNIK_INCLUDE_DIRS)
  set(MAPNIK_LIBRARIES)
endif()


