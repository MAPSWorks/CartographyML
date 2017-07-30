#include "Generators.h"

#include <QImage>
#include <QVariant>

#include "../HeightMap.h"

using namespace TerrainML::Algorithms::Generators;

struct TectonicUpliftFluvialErosion::Private
{
  TerrainML::HeightMap uplift;
  struct RiverNode
  {
    QPointF pt;
  };
  struct RiverEdge
  {
    RiverNode* src;
    RiverNode* dest;
  };
  QList<RiverNode*> nodes;
  QList<RiverEdge*> edges;
};

TectonicUpliftFluvialErosion::TectonicUpliftFluvialErosion() : d(new Private)
{
}

TectonicUpliftFluvialErosion::~TectonicUpliftFluvialErosion()
{
  delete d;
}

void TectonicUpliftFluvialErosion::setUplift(const TerrainML::HeightMap& _data)
{
  d->uplift = _data;
}

void TectonicUpliftFluvialErosion::generateRandomRiverNodes()
{
  
}

TerrainML::HeightMap TectonicUpliftFluvialErosion::generate() const
{
  return TerrainML::HeightMap();
}

QVariantList TectonicUpliftFluvialErosion::riverVertices() const
{
  QVariantList l;
  for(Private::RiverNode* node : d->nodes)
  {
    l.append(QVariant::fromValue(node->pt));
  }
  return l;
}

QVariantList TectonicUpliftFluvialErosion::riverEdges() const
{
  QVariantList l;
  for(Private::RiverEdge* edge : d->edges)
  {
    QVariantMap em;
    em["source"] = d->nodes.indexOf(edge->src);
    em["destination"] = d->nodes.indexOf(edge->dest);
    l.append(em);
  }
  return l;
}

#include "moc_Generators.cpp"
