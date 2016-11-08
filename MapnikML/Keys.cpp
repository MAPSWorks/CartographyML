#include "Keys.h"

#include <QVariant>

using namespace MapnikML;

struct KeyBase::Private
{
  mapnik::keys k;
  QVariant var;
};

KeyBase::KeyBase(mapnik::keys _t, QObject* parent): QObject(parent), d(new Private)
{
  d->k = _t;
}

KeyBase::~KeyBase()
{
  delete d;
}

mapnik::keys KeyBase::key() const
{
  return d->k;
}

QVariant KeyBase::value() const
{
  return d->var;
}

void KeyBase::setValue(const QVariant& _value)
{
  d->var = _value;
  emit(valueChanged());
}

#include "moc_Keys.cpp"
