#include "featureset.h"

#include <GeometryML/Convert/Mapnik.h>
#include <GeometryML/FeaturesSet.h>

using namespace CartographerML::mapnik_interface;

featureset::featureset(GeometryML::FeaturesSet* _features_Set) : m_index(0), m_features_set(_features_Set)
{
}

featureset::~featureset()
{
  delete m_features_set;
}

mapnik::feature_ptr featureset::next()
{
  if(m_index >= m_features_set->featuresCount())
  {
    return mapnik::feature_ptr(nullptr);
  } else {
    return GeometryML::toMapnik(m_features_set->features()[m_index++]);
  }
}


