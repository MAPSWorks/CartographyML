#ifndef _MAPNIKML_ABSTRACT_DATASOURCE_H_
#define _MAPNIKML_ABSTRACT_DATASOURCE_H_

#include <QObject>

#include <mapnik/datasource.hpp>

namespace MapnikML
{
  class AbstractDatasource : public QObject
  {
    Q_OBJECT
  public:
    explicit AbstractDatasource(QObject* parent = 0);
    virtual ~AbstractDatasource();
  public:
    virtual mapnik::datasource_ptr mapnikDatasource() const = 0;
  signals:
    void mapnikDatasourceChanged();
  };
}

#endif
