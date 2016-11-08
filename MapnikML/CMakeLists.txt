set(MAPNIKML_SRCS
  Datasource.cpp
  initialise.cpp
  Keys.cpp
  Layer.cpp
  Map.cpp
  MapElement.cpp
  MapView.cpp
  Rule.cpp
  Symbolizers.cpp
  Style.cpp
  Utils.cpp
  UtilsAttachedProperty.cpp
  )

add_library(MapnikML SHARED ${MAPNIKML_SRCS})
target_link_libraries(MapnikML Qt5::Quick Qt5::Positioning ${MAPNIK_LIBRARIES} ${GDAL_LIBRARY})
