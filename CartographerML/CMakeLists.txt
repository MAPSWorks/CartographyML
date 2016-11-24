set(CARTOGRAPHERML_SRCS
  AbstractFeaturesSource.cpp
  EditableDatasource.cpp
  initialise.cpp
  sources/GDALFeaturesSource.cpp
  mapnik/datasource.cpp
  mapnik/featureset.cpp
  )

add_library(CartographerML SHARED ${CARTOGRAPHERML_SRCS})
target_link_libraries(CartographerML MapnikML GeometryML)
