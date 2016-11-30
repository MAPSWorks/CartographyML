import QtQuick 2.0

import GeometryML 1.0
import CartographerML 1.0
import MapnikML 1.0

Tool
{
  id: root
  
  property QtObject feature
  
  overlayComponent: Item
  {
    Rectangle
    {
      property rect area: tool.feature ? mapView.viewTransform.fromMap(tool.feature.geometry.enveloppe) : Qt.rect(0,0,0,0)
      x: area.x-5
      y: area.y-5
      width: area.width+10
      height: area.height+10
      visible: tool.feature
      color: "#551DB1E1"
      border.color: "white"
      border.width: 1
    }
  }
  optionsComponent: FeatureAttributesTable
  {
    feature: tool.feature
    onFeatureAttributesChanged: featuresSource.record(tool.feature)
  }  
  onPressed:
  {
    var features = featuresSource.featuresAt(mapView.viewTransform.toMap(mouse.x, mouse.y), 1.0 / Math.min(mapView.viewTransform.scaleX, mapView.viewTransform.scaleY))
    if(features.featuresCount > 0)
    {
      var f = features.takeFeature(0)
      if(root.feature != null && f.id == root.feature.id)
      {
        root.feature = null
      } else {
        root.feature = f
      }
    } else {
      root.feature = null
    }
  }
}
