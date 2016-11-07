#include <QGuiApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <MapnikML/initialise.h>

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.addImportPath("qrc:/qml/");

  MapnikML::initialise();
  
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  
  return app.exec();
}
