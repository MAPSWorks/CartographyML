#ifndef _CARTOGRAPHERML_ABSTRACTFEATURESSOURCE_H_
#define _CARTOGRAPHERML_ABSTRACTFEATURESSOURCE_H_

#include <QObject>

namespace CartographerML
{
  class Feature;
  class AbstractFeaturesSource : public QObject
  {
    Q_OBJECT
  public:
    AbstractFeaturesSource(QObject* parent = 0);
    virtual ~AbstractFeaturesSource();
    Q_INVOKABLE virtual QList<Feature*> features(const QRectF& _rect) = 0;
    Q_INVOKABLE virtual QList<Feature*> featuresAt(const QPointF& _rect) = 0;
    Q_INVOKABLE virtual void record(const Feature* _feature) = 0;
  };
}

#endif
