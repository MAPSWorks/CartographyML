import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import TerrainML 1.0
import TerrainMosaic 1.0

ApplicationWindow
{
  id: root
  visible: true
  
  width: 600
  height: 600
  
  HeightMapMosaicView
  {
    anchors.fill: parent
    delegate: HillshadeView
    {
      altitude: 45
    }
    model: TestDatasource {}
  }
  
}

