#include "Spatialite.h"

#include <QByteArray>
#include <QBuffer>
#include <QDataStream>
#include <QDebug>
#include <QRectF>

#include "../Point.h"
#include "../LinearRing.h"
#include "../Polygon.h"

namespace GeometryML
{
  // Specification of Spatialite format can be found at https://www.gaia-gis.it/gaia-sins/BLOB-Geometry.html
  enum SpatialiteType
  {
    PointXY = 1,
    LineStringXY = 2,
    PolygonXY = 3,
    PointXYZ = 1001,
    LineStringXYZ = 1002,
    PolygonXYZ = 1003
  };
  namespace details
  {
    void write(QDataStream& _stream, const Point* _pt, Point::Dimension _dimension)
    {
      switch(_dimension)
      {
        case Point::Dimension::Two:
          _stream << _pt->x() << _pt->y();
          break;
        case Point::Dimension::Three:
          _stream << _pt->x() << _pt->y() << _pt->z();
          break;
        case Point::Dimension::Zero:
          break;
      }
    }
    void write(QDataStream& _stream, const LineString* _linestring, Point::Dimension _dimension)
    {
      _stream << quint32(_linestring->points().size());
      for(const Point* pt : _linestring->points())
      {
        write(_stream, pt, _dimension);
      }
    }
  }
  QByteArray toSpatialite(const Geometry* _geom, quint32 _srid)
  {
    if(_geom->type() == Geometry::Type::Undefined) return QByteArray();
    QBuffer b;
    b.open(QIODevice::WriteOnly);
    QDataStream stream(&b);
    stream << quint8(0x0);
    stream << quint8(0x1);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << _srid;
    QRectF envelope = _geom->enveloppe();
    stream << double(envelope.left()) << double(envelope.top()) << double(envelope.right()) << double(envelope.bottom());
    stream << quint8(0x7C);
    switch(_geom->type())
    {
      case Geometry::Type::Point:
      {
        const Point* pt = static_cast<const Point*>(_geom);
        switch(pt->dimension())
        {
          case Point::Dimension::Zero:
            return QByteArray();
          case Point::Dimension::Two:
            stream << quint32(PointXY) << pt->x() << pt->y();
            break;
          case Point::Dimension::Three:
            stream << quint32(PointXYZ) << pt->x() << pt->y() << pt->z();
            break;
        }
      }
        break;
      case Geometry::Type::Polygon:
      {
        const Polygon* poly = static_cast<const Polygon*>(_geom);
        const Geometry::Dimension d = poly->dimension();
        switch(d)
        {
          case Point::Dimension::Zero:
            return QByteArray();
          case Point::Dimension::Two:
            stream << quint32(PolygonXY);
            break;
          case Point::Dimension::Three:
            stream << quint32(PolygonXYZ);
            break;
        }
        stream << quint32(poly->holes().size() + 1);
        details::write(stream, poly->exteriorRing(), d);
        for(LinearRing* h : poly->holes())
        {
          details::write(stream, h, d);
        }
        break;
      }
      case Geometry::Type::LineString:
      {
        const LineString* ls = static_cast<const LineString*>(_geom);
        const Geometry::Dimension d = ls->dimension();
        switch(d)
        {
          case Point::Dimension::Zero:
            return QByteArray();
          case Point::Dimension::Two:
            stream << quint32(LineStringXY);
            break;
          case Point::Dimension::Three:
            stream << quint32(LineStringXYZ);
            break;
        }
        details::write(stream, ls, d);
        break;
      }
      case Geometry::Type::Collection:
      case Geometry::Type::LinearRing:
      case Geometry::Type::Undefined:
        qFatal("to_spatialite unimplemented");
    }
    stream << quint8(0xFE);
    return b.buffer();
  }
  Geometry* fromSpatialite(const QByteArray& _data, quint32* _srid)
  {
    QBuffer b;
    b.setData(_data);
    b.open(QIODevice::ReadOnly);
    QDataStream stream(&b);
    quint8 start, endian;
    stream >> start;
    stream >> endian;
    if(start != 0)
    {
      qWarning() << "Invalid spatialite blob, expected 0x0 got:" << start;
    }
    switch(endian)
    {
      case 0:
        stream.setByteOrder(QDataStream::BigEndian);
        break;
      case 1:
        stream.setByteOrder(QDataStream::LittleEndian);
        break;
      default:
        qWarning() << "Invalid spatialite blob, invalid endianness:" << endian;
    }
    quint32 srid;
    stream >> srid;
    if(_srid) * _srid = srid;
    double mbr_min_x, mbr_min_y, mbr_max_x, mbr_max_y;
    stream >> mbr_min_x >> mbr_min_y >> mbr_max_x >> mbr_max_y;
    quint8 mbr_end;
    stream >> mbr_end;
    if(mbr_end != 0x7c)
    {
      qWarning() << "Invalid MBR end, expected 0x7c got: " << mbr_end;
    }
    quint32 type;
    stream >> type;
    Geometry* r = nullptr;
    switch(type)
    {
      case PointXY:
      {
        double x, y;
        stream >> x >> y;
        r = new Point(x, y);
      }
        break;
      case PointXYZ:
      {
        double x, y, z;
        stream >> x >> y >> z;
        r = new Point(x, y, z);
      }
        break;
      default:
        qFatal("Unsupported type '%i'", type);
    }
    quint8 last;
    stream >> last;
    if(last != 0xFE)
    {
      qWarning() << "Invalid end of blob, expected 0xFE got: " << last;
    }
    return r;
  }  
}

