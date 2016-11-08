#ifndef _MAPNIKML_UTILS_H_
#define _MAPNIKML_UTILS_H_

#include <QObject>

namespace MapnikML
{
  class UtilsAttachedProperty;
  class Utils : public QObject
  {
    Q_OBJECT
  public:
    static UtilsAttachedProperty *qmlAttachedProperties(QObject *object);
  };
}

#include <QtQml>
QML_DECLARE_TYPEINFO(MapnikML::Utils, QML_HAS_ATTACHED_PROPERTIES)

#endif
