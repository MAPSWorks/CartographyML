#include "Datasource.h"

#include <QDebug>
#include <QMetaProperty>
#include <QList>
#include <QTemporaryDir>
#include <QUrl>

#include <mapnik/config_error.hpp>
#include <mapnik/datasource_cache.hpp>

using namespace MapnikML;

struct Datasource::Private
{
  mutable QList<const char*> properties_name;
  QTemporaryDir tmp_dir;
};

Datasource::Datasource(QObject* parent): AbstractDatasource(parent), d(new Private)
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
        p[pname] = var.value<long int>();
        break;
      case QVariant::LongLong:
        p[pname] = var.value<long int>();
        break;
      case QVariant::Double:
        p[pname] = var.toDouble();
        break;
      case QVariant::Url:
        p[pname] = var.toUrl().toLocalFile().toStdString();
        break;
      case QVariant::String:
      default:
        p[pname] = var.toString().toStdString();
    }
  }
  mapnik::param_map::iterator p_file = p.find("file");
  if(p_file != p.end())
  {
    QString filename = QString::fromStdString(p_file->second.get<std::string>());
    if(filename.startsWith(":/"))
    {
      QString dst = d->tmp_dir.path() + "/shape";
      if(not QFile::copy(filename + ".shp", dst + ".shp"))
      {
        qWarning() << "Failed to copy " << filename + ".shp" << " to " << dst + ".shp";
      }
      if(not QFile::copy(filename + ".dbf", dst + ".dbf"))
      {
        qWarning() << "Failed to copy " << filename + ".dbf" << " to " << dst + ".dbf";
      }
      if(not QFile::copy(filename + ".shx", dst + ".shx"))
      {
        qWarning() << "Failed to copy " << filename + ".shx" << " to " << dst + ".shx";
      }
      
      p_file->second = dst.toStdString();
    }
  }
  
  try
  {
    return mapnik::datasource_cache::instance().create(p);
#if 0
  } catch(const mapnik::config_error& ce)
  {
    qWarning() << "Failed to create datasource: " << ce.what();
    return mapnik::datasource_ptr(nullptr);
#endif
  } catch(const mapnik::datasource_exception& de)
  {
    qWarning() << "Failed to create datasource: " << de.what();
    return mapnik::datasource_ptr(nullptr);
  } catch(const std::runtime_error& re)
  {
    qWarning() << "Failed to create datasource: " << re.what();
    return mapnik::datasource_ptr(nullptr);
  } catch(const std::exception& re)
  {
    qWarning() << "Failed to create datasource: " << re.what();
    return mapnik::datasource_ptr(nullptr);
  }
}


#include "moc_Datasource.cpp"
