#ifndef _MAPNIKML_RULE_H_
#define _MAPNIKML_RULE_H_

#include <QQmlListProperty>

namespace mapnik
{
  class rule;
}

namespace MapnikML
{
  class SymbolizerBase;
  class Rule : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<MapnikML::SymbolizerBase> symbolizers READ symbolizers)
    Q_CLASSINFO("DefaultProperty", "symbolizers")
  public:
    explicit Rule(QObject* parent = 0);
    virtual ~Rule();
    QQmlListProperty<MapnikML::SymbolizerBase> symbolizers() const;
    mapnik::rule mapnikRule();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
