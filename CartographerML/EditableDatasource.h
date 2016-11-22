#ifndef _CARTOGRAPHERML_EDITABLE_DATASOURCE_H_
#define _CARTOGRAPHERML_EDITABLE_DATASOURCE_H_

#include <MapnikML/AbstractDatasource.h>

namespace CartographerML
{
  class AbstractFeaturesSource;
  class EditableDatasource : public MapnikML::AbstractDatasource
  {
    Q_OBJECT
    Q_PROPERTY(CartographerML::AbstractFeaturesSource* featuresSource READ featuresSource WRITE setFeaturesSource NOTIFY featuresSourceChanged)
  public:
    explicit EditableDatasource(QObject* parent = 0);
    virtual ~EditableDatasource();
  public:
    AbstractFeaturesSource* featuresSource() const;
    void setFeaturesSource(AbstractFeaturesSource* _afs);
  public:
    virtual mapnik::datasource_ptr mapnikDatasource() const;
  signals:
    void featuresSourceChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
