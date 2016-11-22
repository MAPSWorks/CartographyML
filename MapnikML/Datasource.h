#ifndef _MAPNIKML_DATASOURCE_H_
#define _MAPNIKML_DATASOURCE_H_

#include "AbstractDatasource.h"

namespace MapnikML
{
  class Datasource : public AbstractDatasource
  {
    Q_OBJECT
  public:
    explicit Datasource(QObject* parent = 0);
    virtual ~Datasource();
  public:
    virtual mapnik::datasource_ptr mapnikDatasource() const;
  private:
    struct Private;
    Private* const d;
  };
}

#endif
