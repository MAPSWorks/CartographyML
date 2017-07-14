qt5_add_resources(GEOMETRYML_QRC_SRC GeometryML.qrc)

set(GEOMETRYML_SRCS
  Collection.cpp
  Feature.cpp
  FeatureAttributesModel.cpp
  FeaturesSet.cpp
  Geometry.cpp
  initialise.cpp
  LinearRing.cpp
  LineString.cpp
  Point.cpp
  Polygon.cpp
  # Convert
  Convert/Gdal.cpp
  Convert/Mapnik.cpp
  Convert/Spatialite.cpp
  # Tools
  Tools/LineString.cpp
  Tools/Polygon.cpp
  )

add_library(GeometryML SHARED ${GEOMETRYML_SRCS} ${GEOMETRYML_QRC_SRC})
target_link_libraries(GeometryML Qt5::Quick)
