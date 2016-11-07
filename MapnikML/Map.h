#ifndef _MAPNIKML_MAP_H_
#define _MAPNIKML_MAP_H_

#include <QQmlListProperty>

namespace MapnikML
{
  class Layer;
  class Map : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<MapnikML::Layer> layers READ layers)
    Q_CLASSINFO("DefaultProperty", "layers")
  public:
    explicit Map(QObject* parent = 0);
    ~Map();
  public:
    QQmlListProperty<Layer> layers() const;
  private:
    struct Private;
    Private* const d;
 };
}

#endif
