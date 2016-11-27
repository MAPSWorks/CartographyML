#include "ViewTransform.h"

#include <QRectF>

using namespace MapnikML;

struct ViewTransform::Private
{
  int width, height;
  QRectF extent;
  qreal scale_x, scale_y;
};

ViewTransform::ViewTransform(int _width, int _height, const QRectF& _extent, QObject* _parent): QObject(_parent), d(new Private)
{
  set(_width, _height, _extent);
}

ViewTransform::~ViewTransform()
{
  delete d;
}

int ViewTransform::height() const
{
  return d->height;
}

int ViewTransform::width() const
{
  return d->width;
}

QRectF ViewTransform::extent() const
{
  return d->extent;
}

void ViewTransform::set(int _width, int _height, const QRectF& _extent)
{
  d->width  = _width;
  d->height = _height;
  d->extent = _extent;
  d->scale_x = _extent.width() > 0 ? d->width / _extent.width() : 1.0;
  d->scale_y = _extent.height() > 0 ? d->height / _extent.height() : 1.0;
}

QPointF ViewTransform::fromMap(qreal x, qreal y) const
{
  return QPointF((x - d->extent.left()) * d->scale_x, (d->extent.bottom() - y) * d->scale_y);
}

QPointF ViewTransform::toMap(qreal x, qreal y) const
{
  return QPointF(d->extent.left() + x / d->scale_x, d->extent.bottom() - y / d->scale_y);
}

#include "moc_ViewTransform.cpp"
