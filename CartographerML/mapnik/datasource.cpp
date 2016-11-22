#include "datasource.h"

#include <QRectF>

#include "AbstractFeaturesSource.h"

using namespace CartographerML::mapnik_interface;

DataSource::DataSource(CartographerML::AbstractFeaturesSource* _source): mapnik::datasource(mapnik::parameters()), m_source(_source)
{

}

mapnik::box2d< double > DataSource::envelope() const
{
  QRectF r = m_source->envelope();
  return mapnik::box2d< double >(r.left(), r.top(), r.right(), r.bottom());
}

mapnik::featureset_ptr DataSource::features(const mapnik::query& q) const
{
  return mapnik::featureset_ptr(nullptr);
}

mapnik::featureset_ptr DataSource::features_at_point(const mapnik::coord2d& pt, double tol) const
{
  return mapnik::featureset_ptr(nullptr);
}

mapnik::layer_descriptor DataSource::get_descriptor() const
{
  return mapnik::layer_descriptor("name", "encoding");
}

mapnik::datasource::datasource_t DataSource::type() const
{
  return datasource_t::Vector;
}

boost::optional< mapnik::datasource_geometry_t > DataSource::get_geometry_type() const
{
  return mapnik::datasource_geometry_t::Collection;
}

