qt5_add_resources(TERRAINML_QRC_SRC TerrainML.qrc)

set(TERRAINML_SRCS
  AbstractDatasource.cpp
  HeightMap.cpp
  HeightMapBaseView.cpp
  HeightMapView.cpp
  HeightMapWrapper.cpp
  HillshadeView.cpp
  initialise.cpp
  Algorithms/rand.cpp
  Algorithms/Generators.cpp
  Algorithms/Hillshade.cpp
  Algorithms/Terraforming.cpp
  ${TERRAINML_QRC_SRC}
  )

add_library(TerrainML SHARED ${TERRAINML_SRCS} )
target_link_libraries(TerrainML Qt5::Gui Qt5::Quick)
