#ifndef _MAPNIKML_UTILS_ATTACHED_PROPERTY_H_
#define _MAPNIKML_UTILS_ATTACHED_PROPERTY_H_

#include <QObject>

namespace MapnikML
{
  class UtilsAttachedProperty : public QObject
  {
    Q_OBJECT
  public:
    UtilsAttachedProperty(QObject* _parent = nullptr);
    ~UtilsAttachedProperty();
    
    Q_INVOKABLE QString wktToProj4(const QString& _srs);
  };
}

#endif
