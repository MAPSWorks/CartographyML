#ifndef _MAPNIKML_LAYER_H_
#define _MAPNIKML_LAYER_H_

#include <QObject>

namespace mapnik
{
  class Map;
}

namespace MapnikML
{
  class Datasource;
  class Layer : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(MapnikML::Datasource* datasource READ datasource WRITE setDatasource NOTIFY datasourceChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  public:
    explicit Layer(QObject* parent = 0);
    virtual ~Layer();
    Datasource* datasource() const;
    void setDatasource(Datasource* _datasource);
    QString name() const;
    void setName(const QString& _name);
    void setMapnikLayer(mapnik::Map* _map, std::size_t _index);
  signals:
    void nameChanged();
    void datasourceChanged();
    void mapnikLayerChanged();
  private slots:
    void updateDatasource();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
