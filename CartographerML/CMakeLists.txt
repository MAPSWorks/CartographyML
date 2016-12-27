qt5_add_resources(CARTOGRAPHERML_QRC_SRC CartographerML.qrc)

set(CARTOGRAPHERML_SRCS
  AbstractFeaturesSource.cpp
  AbstractTool.cpp
  EditableDatasource.cpp
  initialise.cpp
  AbstractTool.h
  ProxyTool.cpp
  Tool.cpp
  ToolController.cpp
  ToolEvents.cpp
  sources/GDALFeaturesSource.cpp
  mapnik/datasource.cpp
  mapnik/featureset.cpp
  ${CARTOGRAPHERML_QRC_SRC}
  )

add_library(CartographerML SHARED ${CARTOGRAPHERML_SRCS})
target_link_libraries(CartographerML MapnikML GeometryML)
