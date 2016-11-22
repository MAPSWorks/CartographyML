#include <mapnik/datasource.hpp>

namespace CartographerML
{
  class AbstractFeaturesSource;
  namespace mapnik
  {
    class DataSource : ::mapnik::datasource
    {
    public:
      DataSource(AbstractFeaturesSource* _source);
      virtual mapnik::box2d< double > envelope() const;
      virtual mapnik::featureset_ptr features(const mapnik::query& q) const;
      virtual mapnik::featureset_ptr features_at_point(const mapnik::coord2d& pt, double tol = 0) const;
      virtual mapnik::layer_descriptor get_descriptor() const;
      virtual boost::optional< mapnik::datasource_geometry_t > get_geometry_type() const;
      virtual datasource_t type() const;
    private:
      AbstractFeaturesSource* m_source;
    };
  }
}
