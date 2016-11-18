import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import MapnikML 1.0

ApplicationWindow
{
  id: root
  visible: true
  
  width: 800
  height: 600
  
  property variant layer_list: []

  FileDialog
  {
    id: openDialog
    title: "Choose a shape file"
    nameFilters: [ "Shape files (*.shp)" ]
    onAccepted: {
      console.log("Loading file: ", fileUrl)
      
      var new_layer = Qt.createQmlObject("import MapnikML 1.0; Layer {}", map, "new layer")
      var new_datasource = Qt.createQmlObject("import MapnikML 1.0; Datasource { property string type: 'shape'; property url file }", new_layer, "new layer")
      new_datasource.file = fileUrl
      new_layer.datasource = new_datasource
      new_layer.styles = ["default"]
      var map_layers = []
      for(var i = 0; i < map.layers.length; ++i)
      {
        map_layers.push(map.layers[i])
      }
      map_layers.push(new_layer)
      map.layers = map_layers
    }
  }
  menuBar: MenuBar {
    Menu {
      title: "Layers"
      MenuItem { action: layer_add_shp }
    }
  }
  Action
  {
    id: layer_add_shp
    text: "Add shp file..."
    onTriggered: openDialog.open()
  }
  MapView
  {
    anchors.fill: parent
    map: Map
    {
      id: map
      backgroundColor: "white"
      styles: [
        Style
        {
          name: "default"
          Rule
          {
            filter: "[mapnik::geometry_type]=point"
            DotSymbolizer
            {
              FillKey { value: "black" }
              WidthKey { value: 5 }
              HeightKey { value: 5 }
            }
          }
          Rule
          {
            filter: "[mapnik::geometry_type]=linestring"
            LineSymbolizer
            {
              StrokeKey { value: "black" }
            }
          }
          Rule
          {
            filter: "[mapnik::geometry_type]=polygon"
            LineSymbolizer
            {
              StrokeKey { value: "black" }
            }
          }
        }
      ]
    }
  }
}
