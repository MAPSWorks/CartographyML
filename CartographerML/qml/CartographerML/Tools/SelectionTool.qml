import QtQuick 2.0

import GeometryML 1.0
import MapnikML 1.0
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
