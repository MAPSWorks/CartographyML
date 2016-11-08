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
      backgroundColor: "skyblue"
      styles: [
        Style
        {
          name: "lakes"
          Rule
          {
            PolygonSymbolizer
            {
              FillKey { value: "blue" }
            }
          }
        },
        Style
        {
          name: "rivers"
          Rule
          {
            LineSymbolizer
            {
              StrokeKey { value: "blue" }
              StrokeLinecapKey { value: Mapnik.ROUND_CAP }
              StrokeLinejoinKey { value: Mapnik.ROUND_JOIN }
            }
          }
        },
        Style
        {
          name: "countries"
          Rule
          {
            filter: "[continent] = 'Europe'"
            PolygonSymbolizer
            {
              FillKey { value: "green" }
            }
          }
          Rule
          {
            filter: "[continent] = 'North America'"
            PolygonSymbolizer
            {
              FillKey { value: "darkorchid" }
            }
          }
          Rule
          {
            filter: "[continent] = 'South America'"
            PolygonSymbolizer
            {
              FillKey { value: "palegreen" }
            }
          }
          Rule
          {
            filter: "[continent] = 'Africa'"
            PolygonSymbolizer
            {
              FillKey { value: "wheat" }
            }
          }
          Rule
          {
            filter: "[continent] = 'Asia'"
            PolygonSymbolizer
            {
              FillKey { value: "lavender" }
            }
          }
          Rule
          {
            filter: "[continent] = 'Oceania'"
            PolygonSymbolizer
            {
              FillKey { value: "olive" }
            }
          }
          Rule
          {
            filter: "[continent] = 'Antarctica'"
            PolygonSymbolizer
            {
              FillKey { value: "lightgray" }
            }
          }
          Rule
          {
            LineSymbolizer
            {
              StrokeKey { value: "black" }
            }
          }
        },
        Style
        {
          name: "populated_places"
          Rule
          {
            filter: "[FEATURECLA] = 'Admin-0 capital'"
            DotSymbolizer
            {
              FillKey { value: "red" }
              WidthKey { value: 5 }
              HeightKey { value: 5 }
            }
          }
          Rule
          {
            filter: "[FEATURECLA] <> 'Admin-0 capital'"
            DotSymbolizer
            {
              FillKey { value: "yellow" }
              WidthKey { value: 5 }
              HeightKey { value: 5 }
            }
          }
        }
      ]
      Layer
      {
        name: "Countries"
        srs: Utils.wktToProj4('GEOGCS["GCS_WGS_1984",DATUM["D_WGS_1984",SPHEROID["WGS_1984",6378137.0,298.257223563]],PRIMEM["Greenwich",0.0],UNIT["Degree",0.0174532925199433]]')
        styles: ["countries"]
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_admin_0_countries"
        }
      }
      Layer
      {
        name: "Rivers"
        srs: Utils.wktToProj4('GEOGCS["GCS_WGS_1984",DATUM["D_WGS_1984",SPHEROID["WGS_1984",6378137,298.257223563]],PRIMEM["Greenwich",0,9],UNIT["Degree",0.017453292519943295]]')
        styles: ["rivers"]
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_rivers_lake_centerlines"
        }
      }
      Layer
      {
        name: "Lakes"
        srs: Utils.wktToProj4('GEOGCS["GCS_WGS_1984",DATUM["D_WGS_1984",SPHEROID["WGS_1984",6378137.0,298.257223563]],PRIMEM["Greenwich",0.0],UNIT["Degree",0.017453292519943295]]')
        styles: ["lakes"]
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_lakes"
        }
      }
      Layer
      {
        name: "Populated places"
        srs: Utils.wktToProj4('GEOGCS["GCS_WGS_1984",DATUM["D_WGS_1984",SPHEROID["WGS_1984",6378137.0,298.257223563]],PRIMEM["Greenwich",0.0],UNIT["Degree",0.017453292519943295]]')
        styles: ["populated_places"]
        datasource: Datasource {
          property string type: "shape"
          property string file: ":/data/ne_110m_populated_places"
        }
      }
    }
  }
}
