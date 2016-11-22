set(CARTOGRAPHERML_SRCS
  AbstractFeaturesSource.cpp
  EditableDatasource.cpp
  Feature.cpp
  initialise.cpp
  sources/GDALFeaturesSource.cpp
  mapnik/datasource.cpp
  )

add_library(CartographerML SHARED ${CARTOGRAPHERML_SRCS})
target_link_libraries(CartographerML MapnikML)
