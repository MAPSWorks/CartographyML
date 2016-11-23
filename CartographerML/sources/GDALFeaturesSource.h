#ifndef _CARTOGRAPHERML_OGRFEATURESSOURCE_H_
#define _CARTOGRAPHERML_OGRFEATURESSOURCE_H_

#include "AbstractFeaturesSource.h"

namespace CartographerML
{
  class GDALFeaturesSource : public AbstractFeaturesSource
  {
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)
  public:
    GDALFeaturesSource(QObject* parent = 0);
    ~GDALFeaturesSource();
  public:
    Q_INVOKABLE virtual bool save();
    Q_INVOKABLE virtual bool load();
    QString errorMessage() const;
    QUrl url() const;
    void setUrl(const QUrl& _name);
  public: // AbstractFeaturesSource
    virtual QList<GeometryML::Feature*> features(const QRectF& _rect);
    virtual QList<GeometryML::Feature*> featuresAt(const QPointF& _rect, qreal _tol = 1e-6);
    virtual void record(const GeometryML::Feature* _feature);
    virtual QRectF envelope();
  signals:
    void urlChanged();
    void errorMessageChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
