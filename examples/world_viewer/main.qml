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
      srs: '+proj=longlat +ellps=WGS84 +no_defs'
      backgroundColor: "white"
      Layer
      {
        name: "Populated places"
        srs: Utils.wktToProj4('GEOGCS["GCS_WGS_1984",DATUM["D_WGS_1984",SPHEROID["WGS_1984",6378137.0,298.257223563]],PRIMEM["Greenwich",0.0],UNIT["Degree",0.017453292519943295]]')
        styles: ["test"]
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_populated_places"
        }
      }
      Layer
      {
        name: "Lakes"
        srs: Utils.wktToProj4('GEOGCS["GCS_WGS_1984",DATUM["D_WGS_1984",SPHEROID["WGS_1984",6378137.0,298.257223563]],PRIMEM["Greenwich",0.0],UNIT["Degree",0.017453292519943295]]')
        styles: ["test"]
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_lakes"
        }
      }
      Layer
      {
        name: "Rivers"
        srs: Utils.wktToProj4('GEOGCS["GCS_WGS_1984",DATUM["D_WGS_1984",SPHEROID["WGS_1984",6378137,298.257223563]],PRIMEM["Greenwich",0,9],UNIT["Degree",0.017453292519943295]]')
        styles: ["test"]
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_rivers_lake_centerlines"
        }
      }
      Layer
      {
        name: "Countries"
        srs: Utils.wktToProj4('GEOGCS["GCS_WGS_1984",DATUM["D_WGS_1984",SPHEROID["WGS_1984",6378137.0,298.257223563]],PRIMEM["Greenwich",0.0],UNIT["Degree",0.0174532925199433]]')
        styles: ["test"]
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_admin_0_countries"
        }
      }
    }
  }
}
