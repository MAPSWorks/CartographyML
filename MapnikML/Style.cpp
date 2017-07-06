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

QQmlListProperty< Rule > Style::rulesQLP() const
{
  return QQmlListProperty<Rule>(const_cast<Style*>(this), &d->rules, &appendRule,&rulesCount,&rulesAt,&rulesClear);
}

void Style::appendRule(QQmlListProperty<Rule>* list, Rule* e)
{
  Style* s = qobject_cast<Style*>(list->object);
  if(s)
  {
    s->d->rules.append(e);
    QObject::connect(e, SIGNAL(ruleChanged()), s, SIGNAL(mapnikStyleChanged()));
  }
}

int Style::rulesCount(QQmlListProperty<Rule>* list)
{
  Style* s = qobject_cast<Style*>(list->object);
  if(s)
  {
    return s->d->rules.size();
  }
  return 0;
}

Rule * Style::rulesAt(QQmlListProperty<Rule>* list, int i)
{
  Style* s = qobject_cast<Style*>(list->object);
  if(s)
  {
    return s->d->rules[i];
  }
  return nullptr;
}

void Style::rulesClear(QQmlListProperty<Rule>* list)
{
  Style* s = qobject_cast<Style*>(list->object);
  if(s)
  {
    for(Rule* r : s->d->rules)
    {
      QObject::disconnect(r, SIGNAL(ruleChanged()), s, SIGNAL(mapnikStyleChanged()));
    }
    s->d->rules.clear();
  }
}


#include "moc_Style.cpp"
