#include "Gdal.h"

#include <memory>

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
  
  Feature* fromGdal(OGRFeature* _feature)
  {
    Feature* f = new Feature(_feature->GetFID());
    switch(_feature->GetGeomFieldCount())
    {
      case 0:
        break;
      case 1:
        f->setGeometry(fromGdal(_feature->GetGeometryRef()));
        break;
      default:
      {
        Collection* c = new Collection;
        for(int i = 0; i < _feature->GetGeomFieldCount(); ++i)
        {
          c->append(fromGdal(_feature->GetGeomFieldRef(i)));
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
          break;
#if GDAL_VERSION_MAJOR >= 2
        case OFTInteger64:
          var = QVariant::fromValue(_feature->GetFieldAsInteger64(i));
          break;
        case OFTInteger64List:
        {
          int count;
          var = QVariant::fromValue(details::to_qlist<qint64>(_feature->GetFieldAsInteger64List(i, &count), count));
        }
          break;
#endif
      }
      
      f->setAttribute(QString::fromLocal8Bit(fd->GetNameRef()), var);
    }
    
    return f;
  }
  
  Feature* fromGdal(OGRFeatureDefn* _definition)
  {
    Feature* f = new Feature(Feature::NO_ID);

    
    for(int i = 0; i < _definition->GetFieldCount(); ++i)
    {
      OGRFieldDefn* fd = _definition->GetFieldDefn(i);
      QVariant var;
      
      switch(fd->GetType())
      {
        case OFTInteger:
          var = QVariant::fromValue(int(0));
          break;
        case OFTIntegerList:
        {
          var = QVariant::fromValue(QList<int>());
        }
          break;
        case OFTReal:
          var = QVariant::fromValue(double(0.0));
          break;
        case OFTRealList:
        {
          var = QVariant::fromValue(QList<double>());
        }
          break;
        case OFTString:
          var = QVariant::fromValue(QString());
          break;
        case OFTStringList:
        {
          var = QVariant::fromValue(QStringList());
        }
          break;
        case OFTBinary:
        {
          var = QVariant::fromValue(QByteArray());
        }
          break;
        case OFTDate:
        {
          var = QVariant::fromValue(QDate());
          break;
        }
        case OFTTime:
        {
          var = QVariant::fromValue(QTime());
          break;
        }
        case OFTDateTime:
        {
          var = QVariant::fromValue(QDateTime());
          break;
        }
        case OFTWideString:
        case OFTWideStringList:
          qWarning() << "Unhandled OFTWideString/OFTWideStringList";
          break;
#if GDAL_VERSION_MAJOR >= 2
        case OFTInteger64:
          var = QVariant::fromValue(qint64(0));
          break;
        case OFTInteger64List:
        {
          var = QVariant::fromValue(QList<qint64>());
        }
          break;
#endif
      }
      
      f->setAttribute(QString::fromLocal8Bit(fd->GetNameRef()), var);
    }
        
    return f;
  }

  namespace details
  {
    template<typename _TO_, typename _TI_>
    _TO_* fromGdal_line_string(_TI_* _from)
    {
      _TO_* to = new _TO_;
      OGRPoint pt;
      for(int i = 0; i < _from->getNumPoints(); ++i)
      {
        _from->getPoint(i, &pt);
        to->append(fromGdal(&pt));
      }
      return to;
    }
  }
  Geometry* fromGdal(OGRGeometry* _geometry)
  {
    OGRPoint* point = dynamic_cast<OGRPoint*>(_geometry);
    if(point)
    {
      return fromGdal(point);
    }
    OGRLinearRing* linear_ring = dynamic_cast<OGRLinearRing*>(_geometry);
    if(linear_ring)
    {
      return details::fromGdal_line_string<LinearRing>(linear_ring);
    }
    OGRLineString* line_string = dynamic_cast<OGRLineString*>(_geometry);
    if(line_string)
    {
      return details::fromGdal_line_string<LineString>(line_string);
    }
    OGRPolygon* polygon = dynamic_cast<OGRPolygon*>(_geometry);
    if(polygon)
    {
      Polygon* p = new Polygon;
      p->setExteriorRing(details::fromGdal_line_string<LinearRing>(polygon->getExteriorRing()));
      for(int i = 0; i < polygon->getNumInteriorRings(); ++i)
      {
        p->appendHole(details::fromGdal_line_string<LinearRing>(polygon->getInteriorRing(i)));
      }
      return p;
    }
    OGRGeometryCollection* collection = dynamic_cast<OGRGeometryCollection*>(_geometry);
    if(collection)
    {
      Collection* c = new Collection;
      for(int i = 0; i < collection->getNumGeometries(); ++i)
      {
        c->append(fromGdal(collection->getGeometryRef(i)));
      }
      return c;
    }
    qWarning() << "Unsupported GDAL geometry: " << _geometry->getGeometryType();
    return nullptr;
  }
  Point* fromGdal(OGRPoint* _point)
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
  namespace details
  {
    template<typename _T_>
    inline _T_* from_qlist(const QList<_T_>& _list)
    {
      _T_* t = new _T_[_list.size()];
      std::copy(_list.begin(), _list.end(), t);
      return t;
    }
    inline char** from_qlist_string(const QStringList& list)
    {
      char** t = new char*[list.size() + 1];
      for(int i = 0; i < list.size(); ++i)
      {
        QByteArray arr = list[i].toUtf8();
        t[i] = new char[arr.size()];
        std::copy(arr.begin(), arr.end(), t[i]);
      }
      t[list.size()] = nullptr;
      return t;
    }
    
  }

  OGRFeature* toGdal(const Feature* _feature, OGRFeatureDefn * _definition)
  {
    OGRFeature* ogr_feature = new OGRFeature(_definition);
    if(_feature->id() == Feature::NO_ID)
    {
      ogr_feature->SetFID(OGRNullFID);
    } else {
      ogr_feature->SetFID(_feature->id());
    }
    ogr_feature->SetGeometryDirectly(toGdal(_feature->geometry()));
    
    for(int i = 0; i < ogr_feature->GetFieldCount(); ++i)
    {
      OGRFieldDefn* fd = ogr_feature->GetFieldDefnRef(i);
      QVariant var = _feature->attribute(QString::fromLocal8Bit(fd->GetNameRef()));
      
      switch(fd->GetType())
      {
        case OFTInteger:
          ogr_feature->SetField(i, var.toInt());
          break;
        case OFTIntegerList:
        {
          QList<int> l = var.value<QList<int>>();
          int* gl = details::from_qlist(l);
          ogr_feature->SetField(i, l.size(), gl);
          delete[] gl;
        }
          break;
        case OFTReal:
          ogr_feature->SetField(i, var.toDouble());
          break;
        case OFTRealList:
        {
          QList<double> l = var.value<QList<double>>();
          double* gl = details::from_qlist(l);
          ogr_feature->SetField(i, l.size(), gl);
          delete[] gl;
        }
          break;
        case OFTString:
          ogr_feature->SetField(i, var.toString().toUtf8().data());
          break;
        case OFTStringList:
        {
          QStringList l = var.value<QStringList>();
          char** gl = details::from_qlist_string(l);
          ogr_feature->SetField(i, gl);
          std::for_each(gl, gl + l.size(), std::default_delete<char>());
          delete[] gl;
        }
          break;
        case OFTBinary:
        {
          QByteArray data = var.toByteArray();
          ogr_feature->SetField(i, data.size(), (GByte*)data.data());
        }
          break;
        case OFTDate:
        {
          QDate d = var.toDate();
          ogr_feature->SetField(i, d.year(), d.month(), d.day());
          break;
        }
        case OFTTime:
        {
          QTime t = var.toTime();
          ogr_feature->SetField(i, 0, 0, 0, t.hour(), t.minute(), t.second());
          break;
        }
        case OFTDateTime:
        {
          QDateTime dt = var.toDateTime();
          QDate d = dt.date();
          QTime t = dt.time();
          ogr_feature->SetField(i, d.year(), d.month(), d.day(), t.hour(), t.minute(), t.second());
          break;
        }
        case OFTWideString:
        case OFTWideStringList:
          qWarning() << "Unhandled OFTWideString/OFTWideStringList";
          break;
#if GDAL_VERSION_MAJOR >= 2
        case OFTInteger64:
          ogr_feature->SetField(i, var.value<qint64>());
          break;
        case OFTInteger64List:
        {
          QList<qint64> l = var.value<QList<qint64>>();
          qint64* gl = details::from_qlist(l);
          ogr_feature->SetField(i, l.size(), gl);
          delete[] gl;
        }
          break;
#endif
      }
    }
    
    return ogr_feature;
  }
  namespace details
  {
    template<typename _OGR_T_>
    _OGR_T_* toGdal_line_string(const Geometry* _geometry)
    {
      _OGR_T_* ogr_ls = new _OGR_T_;
      const LineString* ls = static_cast<const LineString*>(_geometry);
      for(const Point* pt : ls->points())
      {
        OGRPoint* ogr_ptr = toGdal(pt);
        ogr_ls->addPoint(ogr_ptr);
        delete ogr_ptr;
      }
      return ogr_ls;
    }
    template<typename _OGR_T_>
    _OGR_T_* toGdal_collection(const Collection* _collection)
    {
      _OGR_T_* ogr_collection = new _OGR_T_;
      for(Geometry* g : _collection->elements())
      {
        ogr_collection->addGeometryDirectly(toGdal(g));
      }
      return ogr_collection;
    }
  }
  OGRGeometry* toGdal(const Geometry* _geometry)
  {
    switch(_geometry->type())
    {
      case Geometry::Type::Point:
        return toGdal(static_cast<const Point*>(_geometry));
      case Geometry::Type::LineString:
        return  details::toGdal_line_string<OGRLineString>(_geometry);
      case Geometry::Type::LinearRing:
        return  details::toGdal_line_string<OGRLinearRing>(_geometry);
      case Geometry::Type::Polygon:
      {
        const Polygon* polygon = static_cast<const Polygon*>(_geometry);
        OGRPolygon* ogr_polygon = new OGRPolygon;
        ogr_polygon->addRingDirectly(details::toGdal_line_string<OGRLinearRing>(polygon->exteriorRing()));
        for(const LinearRing* lr : polygon->holes())
        {
          ogr_polygon->addRingDirectly(details::toGdal_line_string<OGRLinearRing>(lr));
        }
        return ogr_polygon;
      }
      case Geometry::Type::Collection:
      {
        const Collection* collection = static_cast<const Collection*>(_geometry);
        switch(collection->elementsType())
        {
          case Geometry::Type::Point:
            return details::toGdal_collection<OGRMultiPoint>(collection);
          case Geometry::Type::LineString:
            return details::toGdal_collection<OGRMultiLineString>(collection);
          case Geometry::Type::Polygon:
            return details::toGdal_collection<OGRMultiPolygon>(collection);
          case Geometry::Type::Collection:
          case Geometry::Type::LinearRing:
          case Geometry::Type::Undefined:
            return details::toGdal_collection<OGRGeometryCollection>(collection);
        }
      }
      case Geometry::Type::Undefined:
        return nullptr;
    }
    return nullptr;
  }
  OGRPoint* toGdal(const Point* _point)
  {
    switch(_point->dimension())
    {
      case Point::Dimension::Zero:
        return new OGRPoint;
      case Point::Dimension::Two:
        return new OGRPoint(_point->x(), _point->y());
      case Point::Dimension::Three:
        return new OGRPoint(_point->x(), _point->y(), _point->z());
    }
    qFatal("Invalid point dimension.");
  }
}

