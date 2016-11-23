set(GEOMETRYML_SRCS
  Convert.cpp
  Collection.cpp
  Feature.cpp
  Geometry.cpp
  )

add_library(GeometryML SHARED ${GEOMETRYML_SRCS})
target_link_libraries(GeometryML Qt5::Quick)
