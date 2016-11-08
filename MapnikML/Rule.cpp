#include "Rule.h"

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
  r.set_filter(mapnik::parse_expression(d->expression.toStdString()));
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
}

#include "moc_Rule.cpp"
