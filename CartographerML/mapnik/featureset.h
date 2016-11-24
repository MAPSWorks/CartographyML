#include <mapnik/featureset.hpp>

#include <QList>

namespace GeometryML
{
  class Feature;
}

namespace CartographerML
{
  namespace mapnik_interface
  {
    class featureset : public mapnik::Featureset
    {
    public:
      featureset(const QList<GeometryML::Feature*>& _features);
      virtual ~featureset();
      virtual mapnik::feature_ptr next();
    private:
      int m_index;
      QList<GeometryML::Feature*> m_features;
    };
  }
}

