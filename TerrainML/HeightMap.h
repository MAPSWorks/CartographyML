#include <QSharedDataPointer>

class QRectF;

namespace TerrainML
{
  class HeightMap
  {
  public:
    static constexpr quint16 MAGIC_START      = 0xFE43;
    static constexpr quint16 MAGIC_HEADER_END = 0x780A;
    static constexpr quint16 MAGIC_END        = 0x12BC;
  public:
    HeightMap();
    HeightMap(int _width, int _height, qreal _resolution);
    HeightMap(qreal _origin_x, qreal _origin_y, int _width, int _height, qreal _resolution);
    HeightMap(const HeightMap& _rhs);
    HeightMap& operator=(const HeightMap& _rhs);
    ~HeightMap();
    int width() const;
    int height() const;
    QRectF boundingBox() const;
    void setAltitude(int _x, int _y, float _altitude);
    float altitude(int _x, int _y) const;
    float altitude(qreal _x, qreal _y) const;
    float* data();
    QByteArray toByteArray() const;
    static HeightMap fromByteArray(const QByteArray& _data);
    bool operator==(const HeightMap& _rhs) const;
  private:
    struct Private;
    QSharedDataPointer<Private> d;
  };
}
