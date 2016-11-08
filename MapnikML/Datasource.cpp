#include "Datasource.h"

#include <QDebug>
#include <QMetaProperty>
#include <QList>

#include <mapnik/config_error.hpp>
#include <mapnik/datasource_cache.hpp>

using namespace MapnikML;

struct Datasource::Private
{
  mutable QList<const char*> properties_name;
};

Datasource::Datasource(QObject* parent): QObject(parent), d(new Private)
{
}

Datasource::~Datasource()
{
  delete d;
}

mapnik::datasource_ptr Datasource::mapnikDatasource() const
{
  if(d->properties_name.isEmpty())
  {
    QMetaMethod mDC = metaObject()->method(metaObject()->indexOfMethod("mapnikDatasourceChanged()"));
    for(int i = 0; i < metaObject()->propertyCount(); ++i)
    {
      QMetaProperty p = metaObject()->property(i);
      if(strcmp(p.name(), "objectName") != 0)
      {
        QMetaMethod notif = p.notifySignal();
        d->properties_name.append(p.name());
        connect(this, notif, this, mDC);
      }
    }
  }
  mapnik::parameters p;
  for(const char* pname : d->properties_name)
  {
    QVariant var = property(pname);
    switch(var.type())
    {
      case QVariant::Int:
        p[pname] = var.toInt();
        break;
      case QVariant::Double:
        p[pname] = var.toDouble();
        break;
      case QVariant::String:
      default:
        p[pname] = var.toString().toStdString();
    }
  }
  try
  {
    return mapnik::datasource_cache::instance().create(p);
  } catch(const mapnik::config_error& ce)
  {
    qWarning() << "Failed to create datasource: " << ce.what();
    return mapnik::datasource_ptr(nullptr);
  } catch(const mapnik::datasource_exception& de)
  {
    qWarning() << "Failed to create datasource: " << de.what();
    return mapnik::datasource_ptr(nullptr);
  }
}


#include "moc_Datasource.cpp"
