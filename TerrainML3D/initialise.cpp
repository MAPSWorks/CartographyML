#include <QtQml>

#include <TerrainML/initialise.h>

#include "HeightMapMesh.h"

namespace TerrainML3D
{
  void initialise()
  {
    TerrainML::initialise();
    const char* uri = "TerrainML3D";
    qmlRegisterType<HeightMapMesh>(uri, 1, 0, "HeightMapMesh");
    
  }
}

