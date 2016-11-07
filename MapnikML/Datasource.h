#ifndef _MAPNIKML_DATASOURCE_H_
#define _MAPNIKML_DATASOURCE_H_

#include <QObject>

namespace MapnikML
{
  class Datasource : public QObject
  {
    Q_OBJECT
  public:
    explicit Datasource(QObject* parent = 0);
    virtual ~Datasource();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
