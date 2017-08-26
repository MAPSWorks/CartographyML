#ifndef _TERRAINML_ALGORITHMS_GENERATORS_H_
#define _TERRAINML_ALGORITHMS_GENERATORS_H_

#include <QObject>

namespace TerrainML
{
  class HeightMap;
  namespace Algorithms
  {
    namespace Generators
    {
      /**
       * Somewhat based on the principle 
       * Large Scale Terrain Generation from Tectonic Uplift and Fluvial Erosion
       * https://hal.inria.fr/hal-01262376/document
       */
      class TectonicUpliftFluvialErosion : public QObject
      {
        Q_OBJECT
        Q_PROPERTY(QVariantList riverVertices READ riverVertices  NOTIFY riverNodesChanged)
        Q_PROPERTY(QVariantList riverEdges    READ riverEdges     NOTIFY riverEdgesChanged)
      public:
        TectonicUpliftFluvialErosion();
        ~TectonicUpliftFluvialErosion();
        Q_INVOKABLE void setUplift(const HeightMap& _data);
        Q_INVOKABLE void generateRandomRiverNodes();
        Q_INVOKABLE TerrainML::HeightMap generate() const;
      private:
        QVariantList riverVertices() const;
        QVariantList riverEdges() const;
      signals:
        void riverNodesChanged();
        void riverEdgesChanged();
      private:
        struct Private;
        Private* d;
      };
    }
  }
}

#endif
