set(GEOMETRYML_SRCS
  Convert.cpp
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
  )

add_library(GeometryML SHARED ${GEOMETRYML_SRCS})
target_link_libraries(GeometryML Qt5::Quick)
