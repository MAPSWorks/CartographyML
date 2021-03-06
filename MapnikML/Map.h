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
  class Style;
  class Map : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<MapnikML::Style> styles READ styles)
    Q_PROPERTY(QQmlListProperty<MapnikML::Layer> layers READ layers)
    Q_PROPERTY(QString srs READ srs WRITE setSrs NOTIFY srsChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_CLASSINFO("DefaultProperty", "layers")
  public:
    explicit Map(QObject* parent = 0);
    ~Map();
  public:
    QString srs() const;
    void setSrs(const QString& _srs);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor& _color);
  public:
    QQmlListProperty<Layer> layers() const;
    QQmlListProperty<Style> styles() const;
  public:
    const mapnik::Map& map() const;
  private:
    static void layer_append(QQmlListProperty<Layer>* _list, Layer* _layer);
    static int layer_count(QQmlListProperty<Layer>* _list);
    static Layer* layer_at(QQmlListProperty<Layer>* _list, int _index);
    static void layer_clear(QQmlListProperty<Layer>* _list);
    static void style_append(QQmlListProperty<Style>* _list, Style* _style);
    static int style_count(QQmlListProperty<Style>* _list);
    static Style* style_at(QQmlListProperty<Style>* _list, int _index);
    static void style_clear(QQmlListProperty<Style>* _list);
    Q_INVOKABLE bool load_file(const QString& _filename);
  signals:
    void mapnikMapChanged();
    void srsChanged();
    void backgroundColorChanged();
  private:
    struct Private;
    Private* const d;
 };
}

#endif
