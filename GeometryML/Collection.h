#ifndef _GEOMETRYML_COLLECTION_H_
#define _GEOMETRYML_COLLECTION_H_

#include "Geometry.h"

namespace GeometryML
{
  class Collection : public Geometry
  {
    Q_OBJECT
  public:
    explicit Collection(QObject* parent = 0);
    virtual ~Collection();
    void append(Geometry* _geom);
    QList<Geometry*> elements() const;
  private:
    struct Private;
  };
}

#endif
