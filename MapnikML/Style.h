#ifndef _MAPNIKML_STYLE_H_
#define _MAPNIKML_STYLE_H_

#include <QQmlListProperty>

namespace mapnik
{
  class feature_type_style;
}

namespace MapnikML
{
  class Rule;
  class Style : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<MapnikML::Rule> rules READ rulesQLP)
    Q_CLASSINFO("DefaultProperty", "rules")
  public:
    explicit Style(QObject* parent = 0);
    virtual ~Style();
  public:
    QString name() const;
    void setName(const QString& _name);
  private:
    QQmlListProperty<Rule> rulesQLP() const;
    static void appendRule(QQmlListProperty<Rule> *list, Rule *e);
    static int rulesCount(QQmlListProperty<Rule> *list);
    static Rule* rulesAt(QQmlListProperty<Rule> *list, int i);
    static void rulesClear(QQmlListProperty<Rule> *list);
  public:
    mapnik::feature_type_style mapnikStyle() const;
  signals:
    void nameChanged();
    void mapnikStyleChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
