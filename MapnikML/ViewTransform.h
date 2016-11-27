#ifndef MAPNIKML_VIEWTRANSFORM_H_
#define MAPNIKML_VIEWTRANSFORM_H_


#include <QObject>

#include <QPointF>

namespace MapnikML
{

  class ViewTransform : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(qreal scaleX READ scaleX NOTIFY transformChanged)
    Q_PROPERTY(qreal scaleY READ scaleY NOTIFY transformChanged)
  public:
    ViewTransform(int _width, int _height, const QRectF& _extent, QObject* _parent);
    ~ViewTransform();
  public:
    int width() const;
    int height() const;
    QRectF extent() const;
    
    qreal scaleX() const;
    qreal scaleY() const;

    void set(int _width, int _height, const QRectF& _extent);

  public:
    Q_INVOKABLE QPointF toMap(qreal x, qreal y) const;
    Q_INVOKABLE QPointF toMap(const QPointF& _pt) const
    {
      return toMap(_pt.x(), _pt.y());
    }
    Q_INVOKABLE QPointF fromMap(qreal x, qreal y) const;
    Q_INVOKABLE QPointF fromMap(const QPointF& _pt) const
    {
      return fromMap(_pt.x(), _pt.y());
    }
    
    Q_INVOKABLE QRectF toMap(const QRectF& _pt) const;
    Q_INVOKABLE QRectF fromMap(const QRectF& _pt) const;
  signals:
    void transformChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif