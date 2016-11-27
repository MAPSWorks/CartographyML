import QtQuick 2.0
import QtQuick.Controls 1.2

import GeometryML 1.0
import CartographerML 1.0
import MapnikML 1.0

Tool
{
  id: root
  property MapView mapView
  
  property QtObject feature
  
  overlayComponent: Item
  {
    Rectangle
    {
      property rect area: tool.feature ? mapView.viewTransform.fromMap(tool.feature.geometry.enveloppe) : Qt.rect(0,0,0,0)
      x: area.x
      y: area.y
      width: area.width
      height: area.height
      visible: tool.feature
      color: "#551DB1E1"
      border.color: "white"
      border.width: 1
    }
  }
  
  optionsComponent: TableView {
    model: FeatureAttributesModel {
      feature: tool.feature
    }
    TableViewColumn {
        role: "keyName"
        title: "Name"
        width: 100
    }
    TableViewColumn {
        role: "value"
        title: "Value"
        width: 200
    }
  }
  onPressed:
  {
    var features = featuresSource.featuresAt(mapView.viewTransform.toMap(mouse.x, mouse.y), 1.0 / Math.min(mapView.viewTransform.scaleX, mapView.viewTransform.scaleY))
    if(features.featuresCount > 0)
    {
      var f = features.feature(0)
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
