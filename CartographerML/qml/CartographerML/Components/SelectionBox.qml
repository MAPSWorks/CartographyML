import QtQuick 2.0
import GeometryML 1.0

Rectangle
{
  id: root
  property /*Feature*/ QtObject feature: null
  property /*Geometry*/ QtObject geometry: root.feature ? root.feature.geometry : null
  property rect area: root.geometry ? mapView.viewTransform.fromMap(root.geometry.enveloppe) : Qt.rect(0,0,0,0)
  x: area.x-5
  y: area.y-5
  width: area.width+10
  height: area.height+10
  visible: root.geometry
  color: "#551DB1E1"
  border.color: "white"
  border.width: 1
}

