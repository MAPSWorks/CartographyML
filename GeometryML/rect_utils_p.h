#include <QRectF>

namespace
{

  inline QRectF unite(const QRectF& _r1, const QRectF& _r2)
  {
    return QRectF(QPointF(qMin(_r1.left(), _r2.left()), qMin(_r1.top(), _r2.top())),
                  QPointF(qMax(_r1.right(), _r2.right()), qMax(_r1.bottom(), _r2.bottom())));
  }
}
