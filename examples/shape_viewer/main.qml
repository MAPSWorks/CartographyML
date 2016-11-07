import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import MapnikML 1.0

ApplicationWindow
{
  id: root
  visible: true

  FileDialog
  {
    id: openDialog
    title: "Choose a shape file"
    nameFilters: [ "Shape files (*.shp)" ]
    onAccepted: {
      console.log(fileUrls[0])
    }
  }
  menuBar: MenuBar {
    Menu {
      title: "File"
      MenuItem { action: file_open }
    }
  }
  Action
  {
    id: file_open
    text: "Open..."
    onTriggered: openDialog.open()
  }
  MapView
  {
    map: Map
    {
      Layer
      {
        datasource: Datasource {
          property string type: "shape"
          property string file: ""
        }
      }
    }
  }
}
