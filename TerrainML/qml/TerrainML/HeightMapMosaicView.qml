import QtQuick 2.0

import TerrainML 1.0

Item
{
  id: root
  property Component delegate: HillshadeView {}
  property var model: null
  property rect rect
  property double __coef_h: root.width  / root.rect.width
  property double __coef_v: root.height / root.rect.height
  Repeater
  {
    model: root.model.heightMaps_(root.rect)
    Loader
    {
      property rect __r: HeightMap.boundingBox(modelData)
      x: (__r.x - root.rect.x) * root.__coef_h
      y: (__r.y - root.rect.y) * root.__coef_v
      height: __r.height * root.__coef_v
      width:  __r.width  * root.__coef_h
      sourceComponent: root.delegate
      onLoaded: item.heightMap = modelData
    }
  }
}
