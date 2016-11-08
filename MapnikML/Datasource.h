#ifndef _MAPNIKML_DATASOURCE_H_
#define _MAPNIKML_DATASOURCE_H_

#include <QObject>

#include <mapnik/datasource.hpp>

namespace MapnikML
{
  class Datasource : public QObject
  {
    Q_OBJECT
  public:
    explicit Datasource(QObject* parent = 0);
    virtual ~Datasource();
  public:
    mapnik::datasource_ptr mapnikDatasource() const;
  signals:
    void mapnikDatasourceChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
