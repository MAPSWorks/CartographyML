#include "Style.h"

#include <mapnik/feature_type_style.hpp>
#include <mapnik/rule.hpp>

#include "Rule.h"

using namespace MapnikML;

struct Style::Private
{
  QList<Rule*> rules;
  QString name;
};

Style::Style(QObject* parent): QObject(parent), d(new Private)
{

}

Style::~Style()
{

}

QString Style::name() const
{
  return d->name;
}

void Style::setName(const QString& _name)
{
  d->name = _name;
  emit(nameChanged());
}

mapnik::feature_type_style Style::mapnikStyle() const
{
  mapnik::feature_type_style fts;
  for(Rule* r : d->rules)
  {
    fts.add_rule(r->mapnikRule());
  }
  return fts;
}

QQmlListProperty< Rule > Style::rules() const
{
  return QQmlListProperty< Rule >(const_cast<Style*>(this), d->rules);
}

#include "moc_Style.cpp"
