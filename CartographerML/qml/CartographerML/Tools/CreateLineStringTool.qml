import QtQuick 2.0

import GeometryML 1.0
import CartographerML 1.0

Tool
{
  id: root
  
  property QtObject feature
  hoverEnabled: feature != null
  
  property real __lastMouseX
  property real __lastMouseY

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
    Canvas
    {
      id: overlay_canvas
      anchors.fill: parent
      visible: root.feature
      onPaint:
      {
        if(root.polygon.length == 0) return
        var ctx = getContext('2d');
        ctx.clearRect(0, 0, overlay.width, overlay.height)
        ctx.save()
        ctx.strokeStyle = root.color
        ctx.lineWidth = root.thickness
        ctx.beginPath()
        var pts = root.feature.geometry.points
        var pt = mapView.viewTransform.fromMap(pts[pts.length-1])
        ctx.moveTo(pt.x, pt.y)
        ctx.lineTo(mouseArea.lastMouseX, mouseArea.lastMouseY)
        ctx.stroke()
        ctx.restore()
      }
    }
  }
  optionsComponent: FeatureAttributesTable
  {
    feature: root.feature
    onFeatureAttributesChanged: featuresSource.record(root.feature)
  }  
  onPressed:
  {
    if(mouse.button == Qt.RightButton)
    {
      root.feature = null
    }
    else if(mouse.button == Qt.LeftButton)
    {
      var pt      = mapView.viewTransform.toMap(mouse.x, mouse.y)
      if(root.feature)
      {
        root.feature.geometry.append(pt)
        featuresSource.record(root.feature)
      } else {
        var feature = featuresSource.createFeature()
        feature.geometry = Qt.createQmlObject('import GeometryML 1.0; LineString {}', feature, "CreatePointTool.qml")
        feature.geometry.append(pt)
        if(featuresSource.record(feature))
        {
          root.feature = feature
        } else {
          root.feature = null
        }
      }
    } else {
      mouse.accept = false
    }
  }
  onPositionChanged:
  {
    root.__lastMouseX = mouse.x
    root.__lastMouseY = mouse.y
  }
}
