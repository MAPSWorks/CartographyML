import QtQuick 2.0

import GeometryML 1.0
import CartographerML 1.0
import CartographerML.Components 1.0

Tool
{
  id: root
  
  property QtObject geometry

  hoverEnabled: root.geometry
  
  property real lastMouseX
  property real lastMouseY

  overlayComponent: Item
  {
    SelectionBox
    {
      geometry: root.geometry
    }
    Canvas
    {
      id: overlay_canvas
      anchors.fill: parent
      visible: root.geometry
      property color color: "gray"
      property real thickness: 1
      onPaint:
      {
        if(root.geometry)
        {
          var pts = root.geometry.points
          if(pts.length == 0) return
          var ctx = getContext('2d');
          ctx.clearRect(0, 0, overlay_canvas.width, overlay_canvas.height)
          ctx.save()
          ctx.strokeStyle = overlay_canvas.color
          ctx.lineWidth = overlay_canvas.thickness
          ctx.beginPath()
          var pt_map = pts[pts.length-1]
          var pt = mapView.viewTransform.fromMap(pt_map.x, pt_map.y)
          ctx.moveTo(pt.x, pt.y)
          ctx.lineTo(root.lastMouseX, root.lastMouseY)
          ctx.stroke()
          ctx.restore()
        }
      }
      Connections
      {
        target: root
        onLastMouseXChanged: overlay_canvas.requestPaint()
        onLastMouseYChanged: overlay_canvas.requestPaint()
      }
    }
  }
  function __point_distance_2(pt1, pt2)
  {
    var dx = pt2.x - pt1.x
    var dy = pt2.y - pt1.y
    return dx*dx + dy*dy
  }
  function __point_norm(pt)
  {
    return Math.sqrt(pt.x*pt.x + pt.y*pt.y)
  }
  function __point_normalized(pt)
  {
    return __point_mul_scalar(1.0/__point_norm(pt), pt)
  }
  function __point_addition(pt1, pt2)
  {
    return Qt.point(pt1.x + pt2.x, pt1.y + pt2.y)
  }
  function __point_substraction(pt1, pt2)
  {
    return Qt.point(pt1.x - pt2.x, pt1.y - pt2.y)
  }
  function __point_dot(pt1, pt2)
  {
    return pt1.x * pt2.x + pt1.y * pt2.y
  }
  function __point_mul_scalar(scalar, pt)
  {
    return Qt.point(scalar * pt.x, scalar * pt.y)
  }
  function __projection_line(line_origin, line_dir, point)
  {
    var pt_ = __point_substraction(point, line_origin)
    var pt_proj = __point_mul_scalar(__point_dot(line_dir, pt_), line_dir)
    return __point_addition(line_origin, pt_proj)
  }
  function __compute_snap_pt(mouse)
  {
    var pt      = mapView.viewTransform.toMap(mouse.x, mouse.y)
    
    if(mouse.modifiers & Qt.ShiftModifier)
    {
      var points = root.geometry.points
      var last_point = points[points.length-1]
      var best_pt = Qt.point(last_point.x, pt.y)
      var best_pt_distance = __point_distance_2(best_pt, pt)
      // Compute projection
      var dirs = [ Qt.point(1,0), Qt.point(1/Math.sqrt(2), 1/Math.sqrt(2)), Qt.point(1/Math.sqrt(2), -1/Math.sqrt(2)) ]
      if(points.length >= 2)
      {
        var last_last_point = points[points.length-2]
        var dir = __point_normalized(__point_substraction(last_last_point, last_point))
        var angle = Math.atan2(dir.y, dir.x)
        dirs.push(Qt.point(Math.cos(angle+Math.PI * 0.25), Math.sin(angle+Math.PI * 0.25)))
        dirs.push(Qt.point(Math.cos(angle+Math.PI * 0.50), Math.sin(angle+Math.PI * 0.50)))
        dirs.push(Qt.point(Math.cos(angle+Math.PI * 0.75), Math.sin(angle+Math.PI * 0.75)))
      }
      for(var i = 0; i < dirs.length; ++i)
      {
        var dir = dirs[i]
        var proj = __projection_line(last_point, dir, pt)
        var dist = __point_distance_2(proj, pt)
        if(dist < best_pt_distance)
        {
          best_pt = proj
          best_pt_distance = dist
        }
      }
      
      return best_pt
    }
    
    return pt
  }
  onPressed:
  {
    if(mouse.button == Qt.RightButton)
    {
      root.geometry = null
    }
    else if(mouse.button == Qt.LeftButton)
    {
      var pt      = __compute_snap_pt(mouse)
      if(root.geometry)
      {
        root.geometry.append(pt)
        root.geometryChanged()
      } else {
        root.geometry = Qt.createQmlObject('import GeometryML 1.0; LineString {}', root, "CreatePointTool.qml")
        root.geometry.append(pt)
      }
    } else {
      mouse.accept = false
    }
  }
  onPositionChanged:
  {
    var pt = mapView.viewTransform.fromMap(__compute_snap_pt(mouse))
    root.lastMouseX = pt.x
    root.lastMouseY = pt.y
  }
}
