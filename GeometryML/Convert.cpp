#include "Convert.h"

#include <QDateTime>
#include <QDebug>
#include <QTimeZone>
#include <QVariant>

#include <gdal/ogr_feature.h>

#include "Collection.h"
#include "Feature.h"
#include "LinearRing.h"
#include "Point.h"
#include "Polygon.h"

namespace GeometryML
{
  namespace details
  {
    template<typename _T_>
    inline QList<_T_> to_qlist(const _T_* _ptr, int _count)
    {
      QList<_T_> l;
      for(int i = 0; i < _count; ++i)
      {
        l.append(_ptr[i]);
      }
      return l;
    }
    inline QStringList to_qlist_string( char** _ptr)
    {
      QStringList l;
      for(int i = 0; _ptr[i] != nullptr; ++i)
      {
        l.append(QString::fromLatin1(_ptr[i]));
      }
      return l;
    }
    
  }
  
  Feature* from_gdal(OGRFeature* _feature)
  {
    Feature* f = new Feature(_feature->GetFID());
    switch(_feature->GetGeomFieldCount())
    {
      case 0:
        break;
      case 1:
        f->setGeometry(from_gdal(_feature->GetGeometryRef()));
        break;
      default:
      {
        Collection* c = new Collection;
        for(int i = 0; i < _feature->GetGeomFieldCount(); ++i)
        {
          c->append(from_gdal(_feature->GetGeomFieldRef(i)));
        }
        f->setGeometry(c);
      }
    }
    
    for(int i = 0; i < _feature->GetFieldCount(); ++i)
    {
      OGRFieldDefn* fd = _feature->GetFieldDefnRef(i);
      QVariant var;
      
      switch(fd->GetType())
      {
        case OFTInteger:
          var = QVariant::fromValue(_feature->GetFieldAsInteger(i));
          break;
        case OFTIntegerList:
        {
          int count;
          var = QVariant::fromValue(details::to_qlist<int>(_feature->GetFieldAsIntegerList(i, &count), count));
        }
          break;
        case OFTReal:
          var = QVariant::fromValue(_feature->GetFieldAsDouble(i));
          break;
        case OFTRealList:
        {
          int count;
          var = QVariant::fromValue(details::to_qlist<double>(_feature->GetFieldAsDoubleList(i, &count), count));
        }
          break;
        case OFTString:
          var = QVariant::fromValue(QString::fromLocal8Bit(_feature->GetFieldAsString(i)));
          break;
        case OFTStringList:
        {
          var = QVariant::fromValue(details::to_qlist_string(_feature->GetFieldAsStringList(i)));
        }
          break;
        case OFTBinary:
        {
          int count;
          var = QVariant::fromValue(QByteArray((char*)_feature->GetFieldAsBinary(i, &count), count));
        }
          break;
        case OFTDate:
        {
          int pnYear, pnMonth, pnDay, pnHour, pnMinute, pnSecond, pnTZFlag;
          _feature->GetFieldAsDateTime(i, &pnYear, &pnMonth, &pnDay, &pnHour, &pnMinute, &pnSecond, &pnTZFlag);
          var = QVariant::fromValue(QDate(pnYear, pnMonth, pnDay));
          break;
        }
        case OFTTime:
        {
          int pnYear, pnMonth, pnDay, pnHour, pnMinute, pnSecond, pnTZFlag;
          _feature->GetFieldAsDateTime(i, &pnYear, &pnMonth, &pnDay, &pnHour, &pnMinute, &pnSecond, &pnTZFlag);
          var = QVariant::fromValue(QTime(pnHour, pnMinute, pnSecond));
          break;
        }
        case OFTDateTime:
        {
          int pnYear, pnMonth, pnDay, pnHour, pnMinute, pnSecond, pnTZFlag;
          _feature->GetFieldAsDateTime(i, &pnYear, &pnMonth, &pnDay, &pnHour, &pnMinute, &pnSecond, &pnTZFlag);
          var = QVariant::fromValue(QDateTime(QDate(pnYear, pnMonth, pnDay), QTime(pnHour, pnMinute, pnSecond)));
          break;
        }
        case OFTWideString:
        case OFTWideStringList:
          qWarning() << "Unhandled OFTWideString/OFTWideStringList";
      }
      
      f->setAttribute(QString::fromLocal8Bit(fd->GetNameRef()), var);
    }
    
    return f;
  }
  namespace details
  {
    template<typename _TO_, typename _TI_>
    _TO_* from_gdal_line_string(_TI_* _from)
    {
      _TO_* to = new _TO_;
      OGRPoint pt;
      for(int i = 0; i < _from->getNumPoints(); ++i)
      {
        _from->getPoint(i, &pt);
        to->append(from_gdal(&pt));
      }
      return to;
    }
  }
  Geometry* from_gdal(OGRGeometry* _geometry)
  {
    OGRPoint* point = dynamic_cast<OGRPoint*>(_geometry);
    if(point)
    {
      return from_gdal(point);
    }
    OGRLinearRing* linear_ring = dynamic_cast<OGRLinearRing*>(_geometry);
    if(linear_ring)
    {
      return details::from_gdal_line_string<LinearRing>(linear_ring);
    }
    OGRLineString* line_string = dynamic_cast<OGRLineString*>(_geometry);
    if(line_string)
    {
      return details::from_gdal_line_string<LineString>(line_string);
    }
    OGRPolygon* polygon = dynamic_cast<OGRPolygon*>(_geometry);
    if(polygon)
    {
      Polygon* p = new Polygon;
      p->setExteriorRing(details::from_gdal_line_string<LinearRing>(polygon->getExteriorRing()));
      for(int i = 0; i < polygon->getNumInteriorRings(); ++i)
      {
        p->appendHole(details::from_gdal_line_string<LinearRing>(polygon->getInteriorRing(i)));
      }
      return p;
    }
    OGRGeometryCollection* collection = dynamic_cast<OGRGeometryCollection*>(_geometry);
    if(collection)
    {
      Collection* c = new Collection;
      for(int i = 0; i < collection->getNumGeometries(); ++i)
      {
        c->append(from_gdal(collection->getGeometryRef(i)));
      }
      return c;
    }
    qWarning() << "Unsupported GDAL geometry: " << _geometry->getGeometryType();
    return nullptr;
  }
  Point* from_gdal(OGRPoint* _point)
  {
    switch(_point->getCoordinateDimension())
    {
      default:
      case 0:
        return nullptr;
      case 2:
        return new Point(_point->getX(), _point->getY());
      case 3:
        return new Point(_point->getX(), _point->getY(), _point->getZ());
    }
  }

  OGRFeature* to_gdal(const Feature* _feature)
  {
    return nullptr;
  }
  OGRGeometry* to_gdal(const Geometry* _geometry)
  {
    return nullptr;
  }

  mapnik::feature_ptr to_mapnik(const Feature* _feature)
  {
    mapnik::feature_ptr f(new mapnik::feature_impl(std::make_shared<mapnik::context_type>(), _feature->id()));
    f->set_geometry(to_mapnik(_feature->geometry()));
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
    void to_mapnik_line_string(const LineString* ls, mapnik::geometry::line_string<double>* mls)
    {
      for(Point* pt : ls->points())
      {
        mls->add_coord(pt->x(), pt->y());
      }
    }
    mapnik::geometry::linear_ring<double> to_mapnik(const LinearRing* _lr)
    {
      mapnik::geometry::linear_ring<double> mls;
      to_mapnik_line_string(_lr, &mls);
      return mls;
    }
    template<typename _MT_>
    _MT_ to_mapnik_(const Geometry* _geometry);
    
    template<>
    mapnik::geometry::point<double> to_mapnik_<mapnik::geometry::point<double>>(const Geometry* _geometry)
    {
      const Point* pt = qobject_cast<const Point*>(_geometry);
      return mapnik::geometry::point<double>(pt->x(), pt->y());
    }
    template<>
    mapnik::geometry::line_string<double> to_mapnik_<mapnik::geometry::line_string<double>>(const Geometry* _geometry)
    {
      const LineString* ls = qobject_cast<const LineString*>(_geometry);
      mapnik::geometry::line_string<double> mls;
      details::to_mapnik_line_string(ls, &mls);
      return mls;
    }
    template<>
    mapnik::geometry::polygon<double> to_mapnik_<mapnik::geometry::polygon<double>>(const Geometry* _geometry)
    {
      const Polygon* p = qobject_cast<const Polygon*>(_geometry);
      mapnik::geometry::polygon<double> poly;
      poly.set_exterior_ring(details::to_mapnik(p->exteriorRing()));
      for(const LinearRing* lr : p->holes())
      {
        poly.add_hole(details::to_mapnik(lr));
      }
      return poly;
    }
    
    template<typename _MCT_>
    _MCT_ to_mapnik_multi(const Collection* _collection)
    {
      _MCT_ r;
      for(const Geometry* g : _collection->elements())
      {
        r.push_back(to_mapnik_<typename _MCT_::value_type>(g));
      }
      return r;
    }
    
  }
  mapnik::geometry::geometry<double> to_mapnik(const Geometry* _geometry)
  {
    switch(_geometry->type())
    {
      case Geometry::Type::Point:
      {
        return details::to_mapnik_<mapnik::geometry::point<double>>(_geometry);
      }
      case Geometry::Type::LineString:
      {
        return details::to_mapnik_<mapnik::geometry::line_string<double>>(_geometry);
      }
      case Geometry::Type::LinearRing:
      {
        return details::to_mapnik(qobject_cast<const LinearRing*>(_geometry));
      }
      case Geometry::Type::Polygon:
      {
        return details::to_mapnik_<mapnik::geometry::polygon<double>>(_geometry);
      }
      case Geometry::Type::Collection:
      {
        const Collection* c = qobject_cast<const Collection*>(_geometry);
        switch(c->elementsType())
        {
          case Geometry::Type::Point:
            return details::to_mapnik_multi<mapnik::geometry::multi_point<double>>(c);
          case Geometry::Type::LineString:
            return details::to_mapnik_multi<mapnik::geometry::multi_line_string<double>>(c);
          case Geometry::Type::Polygon:
            return details::to_mapnik_multi<mapnik::geometry::multi_polygon<double>>(c);
          default:
          {
            mapnik::geometry::geometry_collection<double> gc;
            for(const Geometry* g : c->elements())
            {
              gc.push_back(to_mapnik(g));
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
