#ifndef _MAPNIKML_LAYER_H_
#define _MAPNIKML_LAYER_H_

#include <QObject>

namespace MapnikML
{
  class Datasource;
  class Layer : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(MapnikML::Datasource* datasource READ datasource WRITE setDatasource NOTIFY datasourceChanged)
  public:
    explicit Layer(QObject* parent = 0);
    virtual ~Layer();
    Datasource* datasource() const;
    void setDatasource(Datasource* _datasource);
  signals:
    void datasourceChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
