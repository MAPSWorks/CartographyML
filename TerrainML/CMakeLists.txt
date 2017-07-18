set(TERRAINML_SRCS
  HeightMap.cpp
  Algorithms/Hillshade.cpp
  Algorithms/Terraforming.cpp
  )

add_library(TerrainML SHARED ${TERRAINML_SRCS} )
target_link_libraries(TerrainML Qt5::Gui)
