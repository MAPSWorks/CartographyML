#include "EditableDatasource.h"

#include "mapnik/datasource.h"

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
  d->afs = _afs;
  emit(featuresSourceChanged());
  emit(mapnikDatasourceChanged());
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
