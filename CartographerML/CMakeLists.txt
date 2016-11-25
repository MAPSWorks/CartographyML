set(CARTOGRAPHERML_SRCS
  AbstractFeaturesSource.cpp
  AbstractTool.cpp
  EditableDatasource.cpp
  initialise.cpp
  AbstractTool.h
  Tool.cpp
  ToolController.cpp
  ToolEvents.cpp
  sources/GDALFeaturesSource.cpp
  mapnik/datasource.cpp
  mapnik/featureset.cpp
  )

add_library(CartographerML SHARED ${CARTOGRAPHERML_SRCS})
target_link_libraries(CartographerML MapnikML GeometryML)
