import QtQuick 2.0

import GeometryML 1.0
import CartographerML 1.0
import CartographerML.Components 1.0

Tool
{
  id: root
  
  property QtObject feature

  overlayComponent: Item
  {
    SelectionBox
    {
      feature: root.feature
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
