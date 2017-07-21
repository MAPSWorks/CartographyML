#ifndef _TERRAINML_ABSTRACTDATASOURCE_H_
#define _TERRAINML_ABSTRACTDATASOURCE_H_

#include <QObject>

namespace TerrainML
{
  class HeightMap;
  class AbstractDatasource : public QObject
  {
    Q_OBJECT
  public:
    AbstractDatasource(QObject* _parent = nullptr);
    ~AbstractDatasource();
    virtual QList<HeightMap> heightMaps(const QRectF& _rect) const = 0;
  protected:
    Q_INVOKABLE QVariant heightMaps_(const QRectF& _rect) const;
    Q_INVOKABLE QVariant heightMaps_(qreal _x, qreal _y, qreal _width, qreal _height) const;
  };
}

#endif
