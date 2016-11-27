import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import MapnikML 1.0
import CartographerML 1.0

Tool
{
  id: root
  property MapView mapView
  
  property real zoomFactor: 1.05
  property real panFactor: 0.1
  
  property int __isPanning: 0 // 0 no panning 1 mouse pressed 2 panning in progress
  property int  __lastX: -1
  property int  __lastY: -1
  property int __isWheeling: 0 // 0 no wheeling 1 wheeling in progress

  optionsComponent: ColumnLayout
  {
    Button {
      text: "Zoom to fit"
      Layout.fillWidth: true
      onClicked: mapView.zoomToFit()
    }
    Item
    {
      Layout.fillHeight: true
    }
  }
  
  onPressed:
  {
    __isPanning = 1
    __lastX = mouse.x
    __lastY = mouse.y
  }

  onReleased:
  {
    if(__isPanning != 2)
    {
      mapView.panTo(mouse.x, mouse.y)
    }
    __isPanning = 0
  }

  onPositionChanged:
  {
    if (__isPanning > 0)
    {
      __isPanning = 2
      var dx = mouse.x - __lastX
      var dy = mouse.y - __lastY
      mapView.panX -= dx
      mapView.panY -= dy
      __lastX = mouse.x
      __lastY = mouse.y
    }
    if(__isWheeling == 1)
    { // If we are zooming then we should stop
      __isWheeling = 0
      hoverEnabled = false
    }
  }

  onWheel:
  {
    if(wheel.angleDelta.y > 0)
    {
      // First time we zoom in? Then we should record mouse pointer position
      if(__isWheeling == 0)
      {
        __isWheeling = 1
        __lastX = wheel.x
        __lastY = wheel.y
        hoverEnabled = true
      }
      
      // Zoom to point
      mapView.zoomTo(__lastX, __lastY, mapView.zoom * zoomFactor, panFactor)
      
      // Adjust zooming point
      __lastX = (1-panFactor)* zoomFactor*(__lastX - 0.5*mapView.width) + 0.5*mapView.width
      __lastY = (1-panFactor)* zoomFactor*(__lastY - 0.5*mapView.height) + 0.5*mapView.height
    } else {
      mapView.zoomOut(zoomFactor)
    }
  }
  
}
