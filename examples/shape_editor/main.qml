import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import MapnikML 1.0
import CartographerML 1.0

ApplicationWindow
{
  id: root
  visible: true
  
  width: 800
  height: 600
  
  MessageDialog
  {
    id: errorMessageDialog
  }
  
  FileDialog
  {
    id: openDialog
    title: "Choose a shape file"
    nameFilters: [ "Shape files (*.shp)" ]
    onAccepted: {
      
      gdalFeatureSource.url = fileUrl
      if(!gdalFeatureSource.load())
      {
        errorMessageDialog.text = "Error when opening " + fileUrl + ": " + gdalFeatureSource.errorMessage
        errorMessageDialog.open()
      }
    }
  }

  
  menuBar: MenuBar {
    Menu {
      title: "File"
      MenuItem { action: file_open }
      MenuItem { action: file_save }
    }
  }
  Action
  {
    id: file_open
    text: "&Open..."
    onTriggered: openDialog.open()
  }
  Action
  {
    id: file_save
    text: "&Save"
    onTriggered:
    {
      if(!gdalFeatureSource.save())
      {
        errorMessageDialog.text = "Error when opening " + gdalFeatureSource.url + ": " + gdalFeatureSource.errorMessage
        errorMessageDialog.open()
      }
    }
  }
  MapView
  {
    anchors.fill: parent
    map: Map
    {
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
      Layer
      {
        name: "shape_editor"
        styles: ["default"]
        datasource: EditableDatasource
        {
          featuresSource: GDALFeaturesSource {
            id: gdalFeatureSource
          }
        }
      }
    }
  }
}