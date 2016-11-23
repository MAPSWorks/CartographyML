#include "Convert.h"

#include <QDateTime>
#include <QDebug>
#include <QTimeZone>
#include <QVariant>

#include <gdal/ogr_feature.h>

#include "Collection.h"
#include "Feature.h"

namespace GeometryML
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
          var = QVariant::fromValue(to_qlist<int>(_feature->GetFieldAsIntegerList(i, &count), count));
        }
          break;
        case OFTReal:
          var = QVariant::fromValue(_feature->GetFieldAsDouble(i));
          break;
        case OFTRealList:
        {
          int count;
          var = QVariant::fromValue(to_qlist<double>(_feature->GetFieldAsDoubleList(i, &count), count));
        }
          break;
        case OFTString:
          var = QVariant::fromValue(QString::fromLocal8Bit(_feature->GetFieldAsString(i)));
          break;
        case OFTStringList:
        {
          var = QVariant::fromValue(to_qlist_string(_feature->GetFieldAsStringList(i)));
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
  Geometry* from_gdal(OGRGeometry* _geometry)
  {
    return nullptr;
  }
  OGRFeature* to_gdal(const Feature* _feature)
  {
    return nullptr;
  }
  OGRGeometry* to_gdal(const Geometry* _geometry)
  {
    return nullptr;
  }

  mapnik::feature_ptr* to_mapnik(const Feature* _feature)
  {
    return nullptr;
  }
  mapnik::geometry::geometry<double> to_mapnik(const Geometry* _geometry)
  {
    return mapnik::geometry::geometry<double>();
  }
  
}
