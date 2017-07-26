#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <TerrainML3D/initialise.h>

#include "../config.h"

int main(int argc, char *argv[])
{
  QAPPLICATION app(argc, argv);

  QQmlApplicationEngine engine;
  engine.addImportPath("qrc:/qml/");

  TerrainML3D::initialise();
  
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  
  return app.exec();
}
