#include <QJSEngine>

#include "HeightMap.h"
#include "HeightMapView.h"
#include "HeightMapWrapper.h"
#include "HillshadeView.h"

namespace TerrainML
{
  void initialise()
  {
    qRegisterMetaType<TerrainML::HeightMap>("TerrainML::HeightMap");
    
    const char* uri = "TerrainML";
    qmlRegisterType<HeightMapView>(uri, 1, 0, "HeightMapView");
    qmlRegisterType<HillshadeView>(uri, 1, 0, "HillshadeView");
    qmlRegisterSingletonType(uri, 1, 0, "HeightMap", [] (QQmlEngine *engine, QJSEngine *scriptEngine) -> QJSValue
      {
        return scriptEngine->newQObject(new HeightMapWrapper);
      }
      
    );
  }
}

