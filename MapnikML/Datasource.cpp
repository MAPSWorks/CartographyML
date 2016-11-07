#include "Datasource.h"

using namespace MapnikML;

struct Datasource::Private
{
};

Datasource::Datasource(QObject* parent): QObject(parent), d(new Private)
{

}

Datasource::~Datasource()
{

}


#include "moc_Datasource.cpp"
