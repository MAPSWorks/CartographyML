import QtQuick 2.0

import GeometryML 1.0

CreateLineStringGeometryTool
{
  id: root

  property QtObject feature
  
  optionsComponent: FeatureAttributesTable
  {
    feature: root.feature
    onFeatureAttributesChanged: featuresSource.record(root.feature)
  }
  
  onGeometryChanged:
  {
    if(root.geometry == null)
    {
      if(root.feature != null)
      {
        featuresSource.record(root.feature)
      }
    } else if(root.feature == null || root.feature.geometry != root.geometry)
    {
      var feature = featuresSource.createFeature()
      feature.geometry = root.geometry
      if(root.feature && !featuresSource.record(root.feature))
      {
        // TODO report error
        root.geometry = null
        root.feature    = null
      }
    } else if(root.feature.geometry == root.geometry)
    {
      featuresSource.record(root.feature)
    } else {
      console.log("CreateLineSringFeatureTool.qml: INTERNAL ERROR")
    }
  }  
}
