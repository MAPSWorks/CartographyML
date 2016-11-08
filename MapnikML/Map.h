#ifndef _MAPNIKML_MAP_H_
#define _MAPNIKML_MAP_H_

#include <QQmlListProperty>

namespace mapnik
{
  class Map;
}

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
  public:
    const mapnik::Map& map() const;
  private:
    static void layer_append(QQmlListProperty<Layer>* _list, Layer* _layer);
    static int layer_count(QQmlListProperty<Layer>* _list);
    static Layer* layer_at(QQmlListProperty<Layer>* _list, int _index);
    static void layer_clear(QQmlListProperty<Layer>* _list);
  signals:
    void mapnikMapChanged();
  private:
    struct Private;
    Private* const d;
 };
}

#endif
