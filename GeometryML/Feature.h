#ifndef _CARTOGRAPHERML_FEATURE_H_
#define _CARTOGRAPHERML_FEATURE_H_

#include <QObject>

namespace GeometryML
{
  class Geometry;
  class Feature : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QVariantHash attributes READ attributes NOTIFY attributesChanged)
  public:
    explicit Feature(QObject* parent = 0);
    virtual ~Feature();
    Geometry* geometry() const;
    void setGeometry(Geometry* _geometry);
    void setAttribute(const QString& _name, const QVariant& _value);
    QVariant attribute(const QString& _name);
    QVariantHash attributes() const;
  signals:
    void attributesChanged();
    void geometryChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
