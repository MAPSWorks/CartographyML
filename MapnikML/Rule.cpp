#include "Rule.h"

#include <mapnik/config_error.hpp>
#include <mapnik/rule.hpp>

#include "Symbolizers.h"

using namespace MapnikML;

struct Rule::Private
{
  QList<SymbolizerBase*> symbolizers;
  QString expression;
};

Rule::Rule(QObject* parent): QObject(parent), d(new Private)
{
}

Rule::~Rule()
{

}

QQmlListProperty<MapnikML::SymbolizerBase> Rule::symbolizers() const
{
  return QQmlListProperty<MapnikML::SymbolizerBase>(const_cast<Rule*>(this), d->symbolizers);
}

mapnik::rule Rule::mapnikRule()
{
  mapnik::rule r;
  for(SymbolizerBase* sb : d->symbolizers)
  {
    sb->appendMapnikSymbolizer(&r);
  }
  if(not d->expression.isEmpty())
  {
    try
    {
      r.set_filter(mapnik::parse_expression(d->expression.toStdString()));
#if 0
    } catch(mapnik::config_error& ce)
    {
      qWarning() << "mapnik::config_error: " << ce.what();
#endif
    } catch(const std::exception& re)
    {
      qWarning() << "Failed to set filter: " << re.what();
    }
  }
  return r;
}

QString Rule::filter() const
{
  return d->expression;
}

void Rule::setFilter(const QString& _filter)
{
  d->expression = _filter;
  emit(filterChanged());
  emit(ruleChanged());
}

#include "moc_Rule.cpp"
