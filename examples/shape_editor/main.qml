import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import MapnikML 1.0
import CartographerML 1.0
import CartographerML.Tools 1.0
import QtQuick.Layouts 1.0

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
      title: "&File"
      MenuItem { action: file_open }
      MenuItem { action: file_save }
    }
    Menu
    {
      title: "&Tools"
      MenuItem { action: tools_navigation }
      MenuItem { action: tools_selection }
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
  NavigationTool
  {
    id: navigation_tool
    mapView: map_view
  }
  SelectionTool
  {
    id: selection_tool
    featuresSource: gdalFeatureSource
    mapView: map_view
  }
  ExclusiveGroup
  {
    Action
    {
      id: tools_navigation
      text: "&Navigation"
      checkable: true
      checked: true
      onTriggered:
      {
        tool_controller.tool = navigation_tool
      }
    }
    Action
    {
      id: tools_selection
      text: "&Selection"
      checkable: true
      onTriggered:
      {
        tool_controller.tool = selection_tool
      }
    }
  }
  SplitView
  {
    anchors.fill: parent
    orientation: Qt.Horizontal
    Loader
    {
      sourceComponent: tool_controller.tool.optionsComponent
      Layout.minimumWidth: 150
    }
    MapView
    {
      id: map_view
      height: parent.height
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
      ToolController
      {
        id: tool_controller
        anchors.fill: parent
        tool: navigation_tool
      }
      Layout.fillWidth: true
    }
  }
}
