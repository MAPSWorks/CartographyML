import QtQuick 2.0

import GeometryML 1.0
import CartographerML 1.0
import CartographerML.Components 1.0

ProxyTool
{
  id: root
  
  property QtObject feature

  function __record_feature()
  {
    if(root.feature && !featuresSource.record(root.feature))
    {
      root.feature = null
    }
  }
  onFeatureChanged:
  {
    if(root.feature == null)
    {
      tool = defaultTool
    }
  }
  
  optionsComponent: FeatureAttributesTable
  {
    feature: root.feature
    onFeatureAttributesChanged: featuresSource.record(root.feature)
  }
  overlayComponent: root.tool.overlayComponent
  
  Tool
  {
    id: defaultTool
    mapView: root.mapView
    featuresSource: root.featuresSource
    overlayComponent: Item {
      SelectionBox
      {
        feature: root.feature
      }
    }

    onPressed:
    {
      root.feature = featuresSource.createFeature()
      feature.geometry = Qt.createQmlObject('import GeometryML 1.0; Polygon {}', feature, "CreatePolygonFeatureTool.qml")
      feature.geometry.exteriorRing = Qt.createQmlObject('import GeometryML 1.0; LinearRing {}', feature, "CreatePolygonFeatureTool.qml")
      root.tool = lineStringTool
      lineStringTool.geometry = root.feature.geometry.exteriorRing
      if(root.feature && !featuresSource.record(root.feature))
      {
        // TODO report error
        root.geometry = null
        root.feature    = null
      } else {
        mouse.accepted = false // so that the onPressed of CreateLineStringGeometryTool is also called
      }
    }
  }
  CreateLineStringGeometryTool
  {
    id: lineStringTool
    mapView: root.mapView
    featuresSource: root.featuresSource
    onGeometryChanged:
    {
      if(lineStringTool.geometry == null)
      {
        root.tool = defaultTool
      }
      if(root.feature && !featuresSource.record(root.feature))
      {
        // TODO report error
        root.geometry = null
        root.feature    = null
      }
    }
  }
  tool: defaultTool
  
}

