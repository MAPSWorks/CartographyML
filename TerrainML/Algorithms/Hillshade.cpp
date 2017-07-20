#include "Hillshade.h"

#include <cmath>

#include <QDebug>
#include <QImage>

#include "../HeightMap.h"

namespace TerrainML
{
  class HeightMap;
  namespace Algorithms
  {
    namespace details
    {
      inline qreal hillshade_value_at(const HeightMap& _map, int _x, int _y)
      {
        return _map.altitude(qBound(0, _x, _map.width() - 1), qBound(0, _y, _map.height() - 1));
      }
    }
    // From http://edndoc.esri.com/arcobjects/9.2/net/shared/geoprocessing/spatial_analyst_tools/how_hillshade_works.htm
    QImage hillshade(const HeightMap& _map, qreal _altitude, qreal _azimuth)
    {
      qreal zenith = M_PI_2 - _altitude;
      qreal azimuth_math = 2 * M_PI - _azimuth + M_PI_2;
      if(azimuth_math > 2 * M_PI) azimuth_math -= 2 * M_PI;
      QImage image(_map.width(), _map.height(), QImage::Format_Grayscale8);
      for(int y = 0; y < image.height(); ++y)
      {
        for(int x = 0; x < image.width(); ++x)
        {
          qreal a = details::hillshade_value_at(_map, x - 1, y - 1);
          qreal b = details::hillshade_value_at(_map, x    , y - 1);
          qreal c = details::hillshade_value_at(_map, x + 1, y - 1);
          qreal d = details::hillshade_value_at(_map, x - 1, y);
//           qreal e = details::hillshade_value_at(_map, x    , y);
          qreal f = details::hillshade_value_at(_map, x + 1, y);
          qreal g = details::hillshade_value_at(_map, x - 1, y + 1);
          qreal h = details::hillshade_value_at(_map, x    , y + 1);
          qreal i = details::hillshade_value_at(_map, x + 1, y + 1);
          
          qreal dzdx = ((c + 2*f + i) - (a + 2*d + g)) / (8 * _map.resolution());
          qreal dzdy = ((g + 2*h + i) - (a + 2*b + c))  / (8 * _map.resolution());
          
          qreal slope = std::atan(/* z_factor* */ std::sqrt(dzdx * dzdx + dzdy*dzdy));
          qreal aspect = std::atan2(dzdy, -dzdx);
          if(aspect < 0) aspect = 2*M_PI + aspect;
          
          qreal hillshade = 255.0 * ( ( std::cos(zenith) * std::cos(slope) )
                                    + ( std::sin(zenith) * std::sin(slope) * std::cos(azimuth_math - aspect) ) );

          if(hillshade < 0)
          {
            image.scanLine(y)[x] = 0;
          } else {
            image.scanLine(y)[x] = hillshade;
          }
        }
      }
      return image;
    }
  }
}


