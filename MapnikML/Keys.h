#ifndef _MAPNIKML_KEYS_H_
#define _MAPNIKML_KEYS_H_

#include <QColor>
#include <QDebug>
#include <QObject>
#include <QVariant>

#include <mapnik/symbolizer.hpp>

namespace MapnikML
{
  class KeyBase : public QObject
  {
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_CLASSINFO("DefaultProperty", "value")
  public:
    explicit KeyBase(mapnik::keys _t, QObject* parent = 0);
    virtual ~KeyBase();
  public:
    mapnik::keys key() const;
    virtual mapnik::symbolizer_base::value_type mapnikValue() const = 0;
  public:
    QVariant value() const;
    void setValue(const QVariant& _value);
  signals:
    void valueChanged();
  private:
    struct Private;
    Private* const d;
  };
  namespace details
  {
    template<typename _TValue_>
    inline mapnik::symbolizer_base::value_type toMapnikValue(const QVariant& _variant);
    template<>
    inline mapnik::symbolizer_base::value_type toMapnikValue<mapnik::color>(const QVariant& _variant)
    {
      QColor c = _variant.value<QColor>();
      return mapnik::color(c.red(), c.green(), c.blue(), c.alpha());
    }
    template<>
    inline mapnik::symbolizer_base::value_type toMapnikValue<mapnik::line_cap_enum>(const QVariant& _variant)
    {
      return mapnik::line_cap_enum::ROUND_CAP;
    }
    template<>
    inline mapnik::symbolizer_base::value_type toMapnikValue<mapnik::line_join_enum>(const QVariant& _variant)
    {
      return mapnik::line_join_enum::ROUND_JOIN;
    }
  }
  
  template<mapnik::keys _T_, typename _TValue_>
  class Key : public KeyBase
  {
  public:
    explicit Key(QObject* parent = 0) : KeyBase(_T_, parent) {}
    virtual ~Key() {}
    virtual mapnik::symbolizer_base::value_type mapnikValue() const
    {
      return details::toMapnikValue<_TValue_>(value());
    }
  };
}

#endif
