#ifndef _MAPNIKML_SYMBOLIZERS_H_
#define _MAPNIKML_SYMBOLIZERS_H_

#include <QDebug>
#include <QQmlListProperty>
#include <mapnik/rule.hpp>
#include <mapnik/symbolizer.hpp>

#include "Keys.h"

namespace mapnik
{
  class rule;
}

namespace MapnikML
{
  class KeyBase;
  class SymbolizerBase : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<MapnikML::KeyBase> keys READ keys)
    Q_CLASSINFO("DefaultProperty", "keys")
  public:
    explicit SymbolizerBase(QObject* parent = 0);
    virtual ~SymbolizerBase();
  public:
    QQmlListProperty<MapnikML::KeyBase> keys() const;
    virtual void appendMapnikSymbolizer(mapnik::rule* r) = 0;
  protected:
    QList<KeyBase*> keysList() const;
  private:
    struct Private;
    Private* const d;
  };
  
  template<typename _T_>
  class Symbolizer : public SymbolizerBase
  {
  public:
    explicit Symbolizer(QObject* parent = 0) : SymbolizerBase(parent) {}
    virtual ~Symbolizer() {}
    virtual void appendMapnikSymbolizer(mapnik::rule* r)
    {
      _T_ s;
      
      for(KeyBase* kb : keysList())
      {
        mapnik::put(s, kb->key(), kb->mapnikValue());
      }
      r->append(s);
    }
  };
}

#endif
