import CartographerML 1.0
import MapnikML 1.0

Tool
{
  id: root
  property MapView mapView
 
  onPressed:
  {
    var features = featuresSource.featuresAt(mapView.viewTransform.toMap(mouse.x, mouse.y), 1.0).features
    for(var i = 0; i < features.length; ++i)
    {
      var f = features[i]
      console.log("Feature id: ", f.id, "Geometry type: ", f.geometry.type)
      var attrs_keys = f.attributeKeys
      for(var i = 0; i < attrs_keys.length; ++i)
      {
        var k = attrs_keys[i]
        console.log(k, f.attribute(k))
      }
    }
  }
}
