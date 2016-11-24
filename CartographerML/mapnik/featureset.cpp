#include "featureset.h"

#include <GeometryML/Convert.h>

using namespace CartographerML::mapnik_interface;

featureset::featureset(const QList<GeometryML::Feature *>& _features) : m_index(0), m_features(_features)
{
}

featureset::~featureset()
{
}

mapnik::feature_ptr featureset::next()
{
  if(m_index >= m_features.size())
  {
    return mapnik::feature_ptr(nullptr);
  } else {
    return GeometryML::to_mapnik(m_features[m_index++]);
  }
}


