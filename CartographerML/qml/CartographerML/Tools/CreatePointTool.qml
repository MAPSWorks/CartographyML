import QtQuick 2.0

import GeometryML 1.0
import CartographerML 1.0

Tool
{
  id: root
  
  property QtObject feature

  overlayComponent: Item
  {
    Rectangle
    {
      property rect area: root.feature ? mapView.viewTransform.fromMap(root.feature.geometry.enveloppe) : Qt.rect(0,0,0,0)
      x: area.x-5
      y: area.y-5
      width: area.width+10
      height: area.height+10
      visible: root.feature
      color: "#551DB1E1"
      border.color: "white"
      border.width: 1
    }
  }
  optionsComponent: FeatureAttributesTable
  {
    feature: root.feature
    onFeatureAttributesChanged: featuresSource.record(root.feature)
  }  
  onPressed:
  {
    var feature = featuresSource.createFeature()
    var pt      = mapView.viewTransform.toMap(mouse.x, mouse.y)
    feature.geometry = Qt.createQmlObject('import GeometryML 1.0; Point {}', featuresSource, "CreatePointTool.qml")
    feature.geometry.x = pt.x
    feature.geometry.y = pt.y
    if(featuresSource.record(feature))
    {
      root.feature = feature
    } else {
      root.feature = null
    }
  }
}
