#ifndef _MAPNIKML_MAP_ELEMENT_H_
#define _MAPNIKML_MAP_ELEMENT_H_

#include <QObject>

namespace MapnikML
{
  class MapElement : public QObject
  {
    Q_OBJECT
  public:
    explicit MapElement(QObject* parent = 0);
    virtual ~MapElement();
  };
}

#endif
