#ifndef _GEOMETRYML_GEOMETRY_H_
#define _GEOMETRYML_GEOMETRY_H_

#include <QObject>

namespace GeometryML
{
  class Geometry : public QObject
  {
    Q_OBJECT
  protected:
    struct Private;
    Private* const d;
  public:
    enum class Type
    {
      Collection,
      LineSegment,
      Point,
      Polygon,
      Undefined
    };
  protected:
    explicit Geometry(Private* _d, QObject* parent = 0);
  public:
    virtual ~Geometry();
    Type type() const;
  };
}

#endif
