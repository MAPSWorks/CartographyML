#ifndef _GEOMETRYML_FEATURESSET_H_
#define _GEOMETRYML_FEATURESSET_H_

#include <QObject>

namespace GeometryML
{
  class Feature;
  class FeaturesSet : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QRectF enveloppe READ enveloppe NOTIFY featuresChanged)
    Q_PROPERTY(int featuresCount READ featuresCount NOTIFY featuresChanged)
    Q_PROPERTY(QList<QObject*> features READ featuresAsQObject NOTIFY featuresChanged)
  public:
    explicit FeaturesSet(QObject* parent = 0);
    explicit FeaturesSet(const QList<Feature*>& _features, QObject* parent = 0);
    virtual ~FeaturesSet();
    int featuresCount() const;
    QList<Feature*> features() const;
    QRectF enveloppe() const;
  private:
    QList<QObject*> featuresAsQObject();
  signals:
    void featuresChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
