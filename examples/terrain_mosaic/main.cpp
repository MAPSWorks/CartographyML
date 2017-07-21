#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <TerrainML/initialise.h>

#include "../config.h"

#include "TestDatasource.h"

int main(int argc, char *argv[])
{
  QAPPLICATION app(argc, argv);

  QQmlApplicationEngine engine;
  engine.addImportPath("qrc:/qml/");

  TerrainML::initialise();
  
  const char* uri = "TerrainMosaic";
  qmlRegisterType<TestDatasource>(uri, 1, 0, "TestDatasource");
  
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  
  return app.exec();
}

