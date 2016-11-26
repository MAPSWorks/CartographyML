#ifndef _CARTOGRAPHERML_ABSTRACTFEATURESSOURCE_H_
#define _CARTOGRAPHERML_ABSTRACTFEATURESSOURCE_H_

#include <QObject>

namespace GeometryML
{
  class Feature;
  class FeaturesSet;
}

namespace CartographerML
{
  class AbstractFeaturesSource : public QObject
  {
    Q_OBJECT
  public:
    AbstractFeaturesSource(QObject* parent = 0);
    virtual ~AbstractFeaturesSource();
    Q_INVOKABLE virtual GeometryML::FeaturesSet* features(const QRectF& _rect) = 0;
    Q_INVOKABLE virtual GeometryML::FeaturesSet* featuresAt(const QPointF& _rect, qreal _tol = 1e-6) = 0;
    Q_INVOKABLE virtual void record(const GeometryML::Feature* _feature) = 0;
    Q_INVOKABLE virtual QRectF envelope() = 0;
  signals:
    void featuresChanged();
  };
}

#endif
