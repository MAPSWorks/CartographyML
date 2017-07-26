set(TERRAINML3D_SRCS
  HeightMapMesh.cpp
  initialise.cpp)

add_library(TerrainML3D SHARED ${TERRAINML3D_SRCS} )
target_link_libraries(TerrainML3D TerrainML Qt5::3DRender)

  
  
