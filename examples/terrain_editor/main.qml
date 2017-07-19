import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import TerrainML 1.0

ApplicationWindow
{
  id: root
  visible: true
  
  width: 600
  height: 600
  
  HeightMapView
  {
    id: view
    anchors.fill: parent
    Component.onCompleted: {
      var hm = HeightMap.create(-10, -10, 600, 600, 20/600)
      hm = HeightMap.fill(hm, 100.0)
      hm = HeightMap.raise(hm, 0, 0, 10, 5, 2)
      view.heightMap = hm
    }
  }
}
