#ifndef _MAPNIKML_LAYER_H_
#define _MAPNIKML_LAYER_H_

#include "MapElement.h"

namespace mapnik
{
  class Map;
}

namespace MapnikML
{
  class Datasource;
  class Layer : public MapElement
  {
    friend class Map;
    Q_OBJECT
    Q_PROPERTY(MapnikML::Datasource* datasource READ datasource WRITE setDatasource NOTIFY datasourceChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString srs READ srs WRITE setSrs NOTIFY srsChanged)
    Q_PROPERTY(QStringList styles READ styles WRITE setStyles NOTIFY stylesChanged)
  public:
    explicit Layer(QObject* parent = 0);
    virtual ~Layer();
    Datasource* datasource() const;
    void setDatasource(Datasource* _datasource);
    QString name() const;
    void setName(const QString& _name);
    QString srs() const;
    void setSrs(const QString& _srs);
    QStringList styles() const;
    void setStyles(const QStringList& _styles);
  private:
    void setMapnikLayer(mapnik::Map* _map, std::size_t _index);
    void applyStyles();
  signals:
    void nameChanged();
    void srsChanged();
    void datasourceChanged();
    void stylesChanged();
    void mapnikLayerChanged();
  private slots:
    void updateDatasource();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
