import CartographerML 1.0
import MapnikML 1.0

Tool
{
  id: root

  onPressed:
  {
    console.log(featuresSource.featuresAt(mouse.x, mouse.y, 1.0).features.length)
  }
}
