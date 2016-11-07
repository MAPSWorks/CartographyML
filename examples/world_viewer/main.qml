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
    map: Map
    {
      Layer
      {
        datasource: Datasource {
          property string type: "shape"
          property string file: "qrc://data/ne_110m_populated_places.shp"
        }
      }
      Layer
      {
        datasource: Datasource {
          property string type: "shape"
          property string file: "qrc://data/ne_110m_lakes.shp"
        }
      }
      Layer
      {
        datasource: Datasource {
          property string type: "shape"
          property string file: "qrc://data/ne_110m_rivers_lake_centerlines.shp"
        }
      }
      Layer
      {
        datasource: Datasource {
          property string type: "shape"
          property string file: "qrc://data/ne_110m_admin_0_countries.shp"
        }
      }
    }
  }
}
