import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import MapnikML 1.0


ApplicationWindow
{
  id: root
  visible: true
  width: 640
  height: 480
  MapView
  {
    anchors.fill: parent
    map: Map
    {
      Layer
      {
        name: "Populated places"
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_populated_places"
        }
      }
      Layer
      {
        name: "Lakes"
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_lakes"
        }
      }
      Layer
      {
        name: "Rivers"
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_rivers_lake_centerlines"
        }
      }
      Layer
      {
        name: "Countries"
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_admin_0_countries"
        }
      }
    }
  }
}
