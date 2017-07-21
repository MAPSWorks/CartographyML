#include <QJSEngine>

#include "HeightMap.h"
#include "HeightMapView.h"
#include "HeightMapWrapper.h"
#include "HillshadeView.h"

void initialise_TerrainML_qrc()
{
  Q_INIT_RESOURCE(TerrainML);
}

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
      });
    qmlRegisterType(QUrl("qrc:/qml/TerrainML/HeightMapMosaicView.qml"), uri, 1, 0, "HeightMapMosaicView");
  }
}

