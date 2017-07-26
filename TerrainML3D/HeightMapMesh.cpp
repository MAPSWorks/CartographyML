#include "HeightMapMesh.h"

#include <QRectF>
#include <QVector3D>

#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QBufferDataGenerator>

#include <TerrainML/HeightMap.h>

using namespace TerrainML3D;

class HeightMapGeometry : public Qt3DRender::QGeometry
{
  Q_OBJECT
public:
  explicit HeightMapGeometry(QNode *parent = nullptr);
  ~HeightMapGeometry();
  TerrainML::HeightMap heightMap() const
  {
    return m_heightMap;
  }
  void setHeightMap(const TerrainML::HeightMap& _map)
  {
    m_heightMap = _map;
    updateVertices();
    updateIndices();
  }
  qreal baseAltitude() const
  {
    return m_baseAltitude;
  }
  void setBaseAltitude(qreal _baseAltitude)
  {
    updateVertices();
    m_baseAltitude = _baseAltitude;
  }
  void updateVertices();
  void updateIndices();
private:

  TerrainML::HeightMap m_heightMap;
  qreal m_baseAltitude;

  Qt3DRender::QAttribute *m_positionAttribute;
  Qt3DRender::QAttribute *m_normalAttribute;
  Qt3DRender::QAttribute *m_texCoordAttribute;
  Qt3DRender::QAttribute *m_indexAttribute;
  Qt3DRender::QBuffer *m_vertexBuffer;
  Qt3DRender::QBuffer *m_indexBuffer;
};

namespace
{
  int countVertices(const TerrainML::HeightMap& hm)
  {
    return hm.columns() * hm.rows();
  }
  int countFaces(const TerrainML::HeightMap& hm)
  {
    return 2 * (hm.columns() - 1) * (hm.rows() - 1);
  }
}

class HeightMapVertexDataFunctor : public Qt3DRender::QBufferDataGenerator
{
public:
  HeightMapVertexDataFunctor(HeightMapGeometry* _geometry) : m_geometry(_geometry)
  {
  }
  QByteArray operator ()() override
  {
    TerrainML::HeightMap hm = m_geometry->heightMap();
    const int verticesCount = countVertices(hm);
    // vec3 pos, vec2 texCoord, vec3 normal
    const quint32 vertexSize = (3 + 2 + 3) * sizeof(float);

    QByteArray verticesData;
    verticesData.resize(vertexSize * verticesCount);
    float *verticesPtr = reinterpret_cast<float*>(verticesData.data());

    const QPointF orig = hm.boundingBox().topLeft();
    const qreal hr = hm.horizontalResolution();
    const qreal vr = hm.verticalResolution();
    
    // Texture coordinates
    qreal thr = 1.0 / hm.columns();
    qreal tvr = 1.0 / hm.rows();
    
    for(int j = 0; j < hm.rows(); ++j)
    {
      for(int i = 0; i < hm.columns(); ++i)
      {
        QPointF p = orig + QPointF(i*hr, j*vr);
        
        // pos
        *verticesPtr++ = p.x();
        *verticesPtr++ = p.y();
        *verticesPtr++ = hm.altitude(i, j) - m_geometry->baseAltitude();

        // texCoord
        *verticesPtr++ = i * thr;
        *verticesPtr++ = j * tvr;
        
        // Normal // TODO compute one according to the slope
        QVector3D n = hm.normal(i, j);
        *verticesPtr++ = n.x();
        *verticesPtr++ = n.y();
        *verticesPtr++ = n.z();
      }
    }
    
    return verticesData;
  }
  bool operator ==(const QBufferDataGenerator &other) const override
  {
    return this == &other;
  }
  QT3D_FUNCTOR(HeightMapVertexDataFunctor)

private:
  HeightMapGeometry* m_geometry;
};

class HeightMapIndexDataFunctor : public Qt3DRender::QBufferDataGenerator
{
public:
  HeightMapIndexDataFunctor(HeightMapGeometry* _geometry)
      : m_geometry(_geometry)
  {
  }

  QByteArray operator ()() override
  {
    TerrainML::HeightMap hm = m_geometry->heightMap();
    const int facesCount = countFaces(hm);
    const int indicesCount = facesCount * 3;
    const int indexSize = sizeof(quint16);
    Q_ASSERT(indicesCount < 65536);

    QByteArray indicesBytes;
    indicesBytes.resize(indicesCount * indexSize);
    quint16 *indicesPtr = reinterpret_cast<quint16*>(indicesBytes.data());

    for(int j = 0; j < hm.rows() - 1; ++j)
    {
      for(int i = 0; i < hm.columns() - 1; ++i)
      {
        const quint16 a = i + j * hm.columns();
        const quint16 b = a + 1;
        const quint16 c = a + hm.columns();
        const quint16 d = c + 1;
        
        *indicesPtr++ = a;
        *indicesPtr++ = c;
        *indicesPtr++ = b;
        *indicesPtr++ = b;
        *indicesPtr++ = c;
        *indicesPtr++ = d;
      }
    }
    return indicesBytes;
  }

  bool operator ==(const QBufferDataGenerator &other) const override
  {
    return this == &other;
  }
  QT3D_FUNCTOR(HeightMapIndexDataFunctor)

private:
  HeightMapGeometry* m_geometry;
};

HeightMapGeometry::HeightMapGeometry(QNode* parent)
    : QGeometry(parent)
{
  m_positionAttribute = new Qt3DRender::QAttribute(this);
  m_normalAttribute = new Qt3DRender::QAttribute(this);
  m_texCoordAttribute = new Qt3DRender::QAttribute(this);
  m_indexAttribute = new Qt3DRender::QAttribute(this);
  m_vertexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, this);
  m_indexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, this);

  // vec3 pos, vec2 tex, vec3 normal
  const quint32 elementSize = 3 + 2 + 3;
  const quint32 stride = elementSize * sizeof(float);
  const int nVerts = 0;
  const int faces = 0;

  m_positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
//   m_positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
//   m_positionAttribute->setVertexSize(3);
  m_positionAttribute->setDataType(Qt3DRender::QAttribute::Float);
  m_positionAttribute->setDataSize(3);
  m_positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
  m_positionAttribute->setBuffer(m_vertexBuffer);
  m_positionAttribute->setByteStride(stride);
  m_positionAttribute->setCount(nVerts);

  m_texCoordAttribute->setName(Qt3DRender::QAttribute::defaultTextureCoordinateAttributeName());
//   m_texCoordAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
//   m_texCoordAttribute->setVertexSize(2);
  m_texCoordAttribute->setDataType(Qt3DRender::QAttribute::Float);
  m_texCoordAttribute->setDataSize(2);
  m_texCoordAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
  m_texCoordAttribute->setBuffer(m_vertexBuffer);
  m_texCoordAttribute->setByteStride(stride);
  m_texCoordAttribute->setByteOffset(3 * sizeof(float));
  m_texCoordAttribute->setCount(nVerts);

  m_normalAttribute->setName(Qt3DRender::QAttribute::defaultNormalAttributeName());
//   m_normalAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
//   m_normalAttribute->setVertexSize(3);
  m_normalAttribute->setDataType(Qt3DRender::QAttribute::Float);
  m_normalAttribute->setDataSize(3);
  m_normalAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
  m_normalAttribute->setBuffer(m_vertexBuffer);
  m_normalAttribute->setByteStride(stride);
  m_normalAttribute->setByteOffset(5 * sizeof(float));
  m_normalAttribute->setCount(nVerts);

  m_indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
//   m_indexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedShort);
  m_indexAttribute->setDataType(Qt3DRender::QAttribute::UnsignedShort);
  m_indexAttribute->setBuffer(m_indexBuffer);

  m_indexAttribute->setCount(faces * 3);

  addAttribute(m_positionAttribute);
  addAttribute(m_texCoordAttribute);
  addAttribute(m_normalAttribute);
  addAttribute(m_indexAttribute);
}

HeightMapGeometry::~HeightMapGeometry()
{
}

void HeightMapGeometry::updateVertices()
{
  const int nVerts = countVertices(m_heightMap);
  m_positionAttribute->setCount(nVerts);
  m_texCoordAttribute->setCount(nVerts);
  m_normalAttribute->setCount(nVerts);

  m_vertexBuffer->setDataGenerator(QSharedPointer<HeightMapVertexDataFunctor>::create(this));
}

void HeightMapGeometry::updateIndices()
{
  const int faces = countFaces(m_heightMap);
  m_indexAttribute->setCount(faces * 3);
  m_indexBuffer->setDataGenerator(QSharedPointer<HeightMapIndexDataFunctor>::create(this));
}


struct HeightMapMesh::Private
{
  HeightMapGeometry* geometry;
};

HeightMapMesh::HeightMapMesh(Qt3DCore::QNode *parent) : Qt3DRender::QGeometryRenderer(parent), d(new Private)
{
  d->geometry = new HeightMapGeometry(this);
  setGeometry(d->geometry);
}

HeightMapMesh::~HeightMapMesh()
{
  delete d;
}

TerrainML::HeightMap HeightMapMesh::heightMap() const
{
  return d->geometry->heightMap();
}

void HeightMapMesh::setHeightMap(const TerrainML::HeightMap& _map)
{
  d->geometry->setHeightMap(_map);
  emit(heightMapChanged());
}

qreal HeightMapMesh::baseAltitude() const
{
  return d->geometry->baseAltitude();
}

void HeightMapMesh::setBaseAltitude(qreal _baseAltitude)
{
  d->geometry->setBaseAltitude(_baseAltitude);
  emit(baseAltitudeChanged());
}

#include "HeightMapMesh.moc"
#include "moc_HeightMapMesh.cpp"
