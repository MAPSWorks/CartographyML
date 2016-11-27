#include <QCommandLineParser>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <CartographerML/initialise.h>

#include "../config.h"

int main(int argc, char *argv[])
{
  QAPPLICATION app(argc, argv);
  QCoreApplication::setApplicationName("shape_editor");
  QCoreApplication::setApplicationVersion("1.0");
    
  QCommandLineParser parser;
  parser.setApplicationDescription("SHP file editor.");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("shpfile", QCoreApplication::tr("main", "Open the given file"));
  
  if (!parser.parse(QCoreApplication::arguments()))
  {
    qWarning() << "Failed to parse command line" << parser.errorText();
    return -1;
  }
  
  QString filename;
  if(parser.positionalArguments().size() == 1)
  {
    filename = parser.positionalArguments().first();
  }

  QQmlApplicationEngine engine;
  engine.addImportPath("qrc:/qml/");

  CartographerML::initialise();
  
  engine.rootContext()->setContextProperty("CMD_LINE_FILENAME", filename);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  
  return app.exec();
}
