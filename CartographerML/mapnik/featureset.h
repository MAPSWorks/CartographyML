#include <mapnik/featureset.hpp>

#include <QList>

namespace GeometryML
{
  class FeaturesSet;
}

namespace CartographerML
{
  namespace mapnik_interface
  {
    class featureset : public mapnik::Featureset
    {
    public:
      featureset(GeometryML::FeaturesSet* _features_set);
      virtual ~featureset();
      virtual mapnik::feature_ptr next();
    private:
      int m_index;
      GeometryML::FeaturesSet* m_features_set;
    };
  }
}

