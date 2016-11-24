#include "EditableDatasource.h"

#include "mapnik/datasource.h"

#include "AbstractFeaturesSource.h"

using namespace CartographerML;

struct EditableDatasource::Private
{
  AbstractFeaturesSource* afs = nullptr;
};

EditableDatasource::EditableDatasource(QObject* parent): AbstractDatasource(parent), d(new Private)
{

}

EditableDatasource::~EditableDatasource()
{
  delete d;
}

AbstractFeaturesSource* EditableDatasource::featuresSource() const
{
  return d->afs;
}

void EditableDatasource::setFeaturesSource(AbstractFeaturesSource* _afs)
{
  if(d->afs)
  {
    disconnect(d->afs, SIGNAL(featuresChanged()), this, SIGNAL(mapnikDatasourceChanged()));
  }
  d->afs = _afs;
  d->afs->setParent(this);
  emit(featuresSourceChanged());
  emit(mapnikDatasourceChanged());
  connect(d->afs, SIGNAL(featuresChanged()), SIGNAL(mapnikDatasourceChanged()));
}

mapnik::datasource_ptr EditableDatasource::mapnikDatasource() const
{
  if(d->afs)
  {
    return mapnik::datasource_ptr(new CartographerML::mapnik_interface::DataSource(d->afs));
  } else {
    return mapnik::datasource_ptr(nullptr);
  }
}

#include "moc_EditableDatasource.cpp"
