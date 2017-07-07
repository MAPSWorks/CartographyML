#ifndef _GEOMETRYML_COLLECTION_H_
#define _GEOMETRYML_COLLECTION_H_

#include "Geometry.h"

namespace GeometryML
{
  class Collection : public Geometry
  {
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> elements READ elementsAsQObject NOTIFY elementsChanged)
    Q_PROPERTY(Type elementsType READ elementsType NOTIFY elementsTypeChanged)
  public:
    explicit Collection(QObject* parent = 0);
    virtual ~Collection();
    void append(Geometry* _geom);
    QList<Geometry*> elements() const;
    Type elementsType() const;
    QRectF enveloppe() const override;
    Dimension dimension() const override;
  private:
    QList<QObject*> elementsAsQObject();
  signals:
    void elementsChanged();
    void elementsTypeChanged();
  private:
    struct Private;
  };
}

#endif
