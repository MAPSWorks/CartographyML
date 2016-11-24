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
    Feature* f = new Feature;
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
    return mapnik::feature_ptr(nullptr);
  }
  mapnik::geometry::geometry<double> to_mapnik(const Geometry* _geometry)
  {
    return mapnik::geometry::geometry<double>();
  }
  
}
