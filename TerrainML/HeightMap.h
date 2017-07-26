#include <QSharedDataPointer>

class QImage;
class QPointF;
class QRectF;
class QVector3D;

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
    HeightMap(qreal _width, qreal _height, qreal _resolution);
    HeightMap(qreal _origin_x, qreal _origin_y, qreal _width, qreal _height, qreal _resolution);
    HeightMap(const HeightMap& _rhs);
    HeightMap& operator=(const HeightMap& _rhs);
    ~HeightMap();
    int columns() const;
    int rows() const;
    qreal horizontalResolution() const;
    qreal verticalResolution() const;
    QPointF origin() const;
    QRectF boundingBox() const;
    void setAltitude(int _x, int _y, float _altitude);
    QPair<float, float> minmax() const;
    float altitude(int _x, int _y) const;
    float altitude(qreal _x, qreal _y) const;
    QVector3D normal(int _x, int _y) const;
    float* data();
    QImage toImage() const;
    QByteArray toByteArray() const;
    static HeightMap fromByteArray(const QByteArray& _data);
    bool operator==(const HeightMap& _rhs) const;
  private:
    struct Private;
    QSharedDataPointer<Private> d;
  };
}

#include <QMetaType>

Q_DECLARE_METATYPE(TerrainML::HeightMap)
