import QtQuick 2.0

import GeometryML 1.0
import CartographerML 1.0
import MapnikML 1.0

Tool
{
  id: root
  property MapView mapView
  
  property QtObject features
  
  overlayComponent: Item
  {
    Rectangle
    {
      property rect area: tool.features ? mapView.viewTransform.fromMap(tool.features.enveloppe) : Qt.rect(0,0,0,0)
      x: area.x
      y: area.y
      width: area.width
      height: area.height
      visible: tool.features && tool.features.featuresCount > 0
      color: "#551DB1E1"
      border.color: "white"
      border.width: 1
    }
  }
 
  onPressed:
  {
    root.features = featuresSource.featuresAt(mapView.viewTransform.toMap(mouse.x, mouse.y), 1.0 / Math.min(mapView.viewTransform.scaleX, mapView.viewTransform.scaleY))
  }
}
