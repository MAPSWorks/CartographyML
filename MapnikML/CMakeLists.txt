set(MAPNIKML_SRCS
  Datasource.cpp
  initialise.cpp
  Layer.cpp
  Map.cpp
  MapView.cpp )

add_library(MapnikML SHARED ${MAPNIKML_SRCS})
target_link_libraries(MapnikML Qt5::Quick Qt5::Positioning ${MAPNIK_LIBRARIES})
  