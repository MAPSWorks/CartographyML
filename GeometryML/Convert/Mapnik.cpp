#include "Mapnik.h"

#include <QDateTime>
#include <QDebug>
#include <QTimeZone>
#include <QVariant>

#include "Collection.h"
#include "Feature.h"
#include "LinearRing.h"
#include "Point.h"
#include "Polygon.h"

namespace GeometryML
{
  mapnik::feature_ptr toMapnik(const Feature* _feature)
  {
    mapnik::feature_ptr f(new mapnik::feature_impl(std::make_shared<mapnik::context_type>(), _feature->id()));
    f->set_geometry(toMapnik(_feature->geometry()));
    QVariantHash attr = _feature->attributes();
    for(QVariantHash::const_iterator it = attr.begin(); it != attr.end(); ++it)
    {
      mapnik::value val;
      switch(it.value().type())
      {
        case QVariant::Bool:
          val = mapnik::value(it.value().toBool());
          break;
        case QVariant::Int:
          val = mapnik::value(it.value().toInt());
          break;
        case QVariant::Double:
          val = mapnik::value(it.value().toDouble());
          break;
        default:
          val = mapnik::value(mapnik::value_unicode_string(it.value().toString().toUtf8().data()));
          break;
      }
      f->put_new(it.key().toStdString(), val);
    }
    return f;
  }
  namespace details
  {
    void toMapnik_line_string(const LineString* ls, mapnik::geometry::line_string<double>* mls)
    {
      for(Point* pt : ls->points())
      {
        mls->add_coord(pt->x(), pt->y());
      }
    }
    mapnik::geometry::linear_ring<double> toMapnik(const LinearRing* _lr)
    {
      mapnik::geometry::linear_ring<double> mls;
      toMapnik_line_string(_lr, &mls);
      return mls;
    }
    template<typename _MT_>
    _MT_ toMapnik_(const Geometry* _geometry);
    
    template<>
    mapnik::geometry::point<double> toMapnik_<mapnik::geometry::point<double>>(const Geometry* _geometry)
    {
      const Point* pt = qobject_cast<const Point*>(_geometry);
      return mapnik::geometry::point<double>(pt->x(), pt->y());
    }
    template<>
    mapnik::geometry::line_string<double> toMapnik_<mapnik::geometry::line_string<double>>(const Geometry* _geometry)
    {
      const LineString* ls = qobject_cast<const LineString*>(_geometry);
      mapnik::geometry::line_string<double> mls;
      details::toMapnik_line_string(ls, &mls);
      return mls;
    }
    template<>
    mapnik::geometry::polygon<double> toMapnik_<mapnik::geometry::polygon<double>>(const Geometry* _geometry)
    {
      const Polygon* p = qobject_cast<const Polygon*>(_geometry);
      mapnik::geometry::polygon<double> poly;
      poly.set_exterior_ring(details::toMapnik(p->exteriorRing()));
      for(const LinearRing* lr : p->holes())
      {
        poly.add_hole(details::toMapnik(lr));
      }
      return poly;
    }
    
    template<typename _MCT_>
    _MCT_ toMapnik_multi(const Collection* _collection)
    {
      _MCT_ r;
      for(const Geometry* g : _collection->elements())
      {
        r.push_back(toMapnik_<typename _MCT_::value_type>(g));
      }
      return r;
    }
    
  }
  mapnik::geometry::geometry<double> toMapnik(const Geometry* _geometry)
  {
    switch(_geometry->type())
    {
      case Geometry::Type::Point:
      {
        return details::toMapnik_<mapnik::geometry::point<double>>(_geometry);
      }
      case Geometry::Type::LineString:
      {
        return details::toMapnik_<mapnik::geometry::line_string<double>>(_geometry);
      }
      case Geometry::Type::LinearRing:
      {
        return details::toMapnik(qobject_cast<const LinearRing*>(_geometry));
      }
      case Geometry::Type::Polygon:
      {
        return details::toMapnik_<mapnik::geometry::polygon<double>>(_geometry);
      }
      case Geometry::Type::Collection:
      {
        const Collection* c = qobject_cast<const Collection*>(_geometry);
        switch(c->elementsType())
        {
          case Geometry::Type::Point:
            return details::toMapnik_multi<mapnik::geometry::multi_point<double>>(c);
          case Geometry::Type::LineString:
            return details::toMapnik_multi<mapnik::geometry::multi_line_string<double>>(c);
          case Geometry::Type::Polygon:
            return details::toMapnik_multi<mapnik::geometry::multi_polygon<double>>(c);
          default:
          {
            mapnik::geometry::geometry_collection<double> gc;
            for(const Geometry* g : c->elements())
            {
              gc.push_back(toMapnik(g));
            }
            return gc;
          }
        }
        
      }
      case Geometry::Type::Undefined:
        return mapnik::geometry::geometry<double>();
    }
    qFatal("Internal error");
  }
  
}

