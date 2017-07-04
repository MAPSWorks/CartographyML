#include <qglobal.h>

class QByteArray;

namespace GeometryML
{
  class Geometry;
  QByteArray toSpatialite(const Geometry* _point, quint32 _srid);
  Geometry* fromSpatialite(const QByteArray& _data, quint32* _srid);
}

