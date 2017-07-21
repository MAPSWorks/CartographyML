import QtQuick 2.0

import TerrainML 1.0

Item
{
  id: root
  property Component delegate: HillshadeView {}
  property var model: null
  property rect rect
  Repeater
  {
    model: root.model.heightMaps_(root.rect)
    Loader
    {
      sourceComponent: root.delegate
      onLoaded: item.heightMap = modelData
    }
  }
}
