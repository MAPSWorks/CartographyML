#include "LinearRing.h"

#include "LineString_p.h"

using namespace GeometryML;

LinearRing::LinearRing(QObject* parent): LineString(new LineString::Private(Type::LinearRing), parent)
{

}

LinearRing::~LinearRing()
{

}

#include "moc_LinearRing.cpp"
