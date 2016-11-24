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
    Q_PROPERTY(qint64 id READ id WRITE setId NOTIFY idChanged);
    Q_PROPERTY(GeometryML::Geometry* geometry READ geometry WRITE setGeometry NOTIFY geometryChanged);
  public:
    Feature(qint64 _id, QObject* parent = 0);
    virtual ~Feature();
    qint64 id() const;
    void setId(qint64 _id);
    Geometry* geometry() const;
    void setGeometry(Geometry* _geometry);
    void setAttribute(const QString& _name, const QVariant& _value);
    QVariant attribute(const QString& _name);
    QVariantHash attributes() const;
  signals:
    void attributesChanged();
    void geometryChanged();
    void idChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
