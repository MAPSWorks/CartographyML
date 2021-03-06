#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <TerrainML/initialise.h>

#include "../config.h"

int main(int argc, char *argv[])
{
  QAPPLICATION app(argc, argv);

  QQmlApplicationEngine engine;
  engine.addImportPath("qrc:/qml/");

  TerrainML::initialise();
  
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  
  return app.exec();
}
