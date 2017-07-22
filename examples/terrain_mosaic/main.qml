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
  
  ColumnLayout
  {
    anchors.fill: parent
    RowLayout
    {
      Text { text: "Azimuth: " }
      Slider {
        id: azimuthSlider
        minimumValue: 0
        maximumValue: 360
      }
      Text { text: azimuthSlider.value }
    }
    RowLayout
    {
      Text { text: "Altitude: " }
      Slider {
        id: altitudeSlider
        minimumValue: 0
        value: 45
        maximumValue: 90
      }
      Text { text: altitudeSlider.value }
    }
    RowLayout
    {
      Text { text: "Intensity: " }
      Slider {
        id: intensitySlider
        minimumValue: 0
        value: 80.0
        maximumValue: 255.0
      }
      Text { text: intensitySlider.value }
    }
    HeightMapMosaicView
    {
      clip: true
      delegate: HillshadeView
      {
        altitude: altitudeSlider.value
        azimuth: azimuthSlider.value
        intensity: intensitySlider.value
      }
      rect.x: -1
      rect.y: -1
      rect.width: 3
      rect.height: 5
      model: TestDatasource {}
      Layout.fillWidth: true
      Layout.fillHeight: true
    }
  }
  
}

