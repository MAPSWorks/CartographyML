import CartographerML 1.0
import MapnikML 1.0

Tool
{
  id: root
  property MapView mapView
 
  onPressed:
  {
    console.log(featuresSource.featuresAt(mapView.viewTransform.toMap(mouse.x, mouse.y), 1.0).features.length)
  }
}
