import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import TerrainML 1.0

ApplicationWindow
{
  id: root
  visible: true
  
  width: 600
  height: 600
  
  SplitView
  {
    anchors.fill: parent
    HeightMapView
    {
      id: view
      Component.onCompleted: {
        var hm = HeightMap.create(-10, -10, 20, 20, 20/600)
        hm = HeightMap.fill(hm, 100.0)
        hm = HeightMap.raise(hm, 0, 0, 10, 5, 2)
        view.heightMap = hm
      }
      Layout.fillWidth: true
      Layout.fillHeight: true
    }
    ColumnLayout
    {
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
      HillshadeView
      {
        azimuth: azimuthSlider.value
        altitude: altitudeSlider.value
        intensity: intensitySlider.value
        heightMap: view.heightMap
        Layout.fillWidth: true
        Layout.fillHeight: true
      }
    }
  }
}
