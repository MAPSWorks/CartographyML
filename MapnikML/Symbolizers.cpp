#include "Symbolizers.h"

#include "Keys.h"

using namespace MapnikML;

struct SymbolizerBase::Private
{
  QList<MapnikML::KeyBase*> keys;
};

SymbolizerBase::SymbolizerBase(QObject* parent): QObject(parent), d(new Private)
{

}

SymbolizerBase::~SymbolizerBase()
{

}

QQmlListProperty<KeyBase> SymbolizerBase::keys() const
{
  return QQmlListProperty<KeyBase>(const_cast<SymbolizerBase*>(this), d->keys);
}

QList< KeyBase* > SymbolizerBase::keysList() const
{
  return d->keys;
}

#include "moc_Symbolizers.cpp"
