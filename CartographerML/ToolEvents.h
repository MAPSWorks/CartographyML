#ifndef _CARTOGRAPHERML_TOOLEVENTS_H_
#define _CARTOGRAPHERML_TOOLEVENTS_H_

#include <QKeyEvent>
#include <QMouseEvent>

namespace CartographerML
{
  class KeyToolEvent : public QObject
  {
      Q_OBJECT
      Q_PROPERTY(int key READ key)
      Q_PROPERTY(QString text READ text)
      Q_PROPERTY(int modifiers READ modifiers)
      Q_PROPERTY(bool isAutoRepeat READ isAutoRepeat)
      Q_PROPERTY(int count READ count)
      Q_PROPERTY(quint32 nativeScanCode READ nativeScanCode)
      Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)
  public:
      KeyToolEvent() : event(QEvent::None, 0, Qt::NoModifier)
      {}
      void reset(const QKeyEvent &ke)
      {
          event = ke;
      }
      int key() const { return event.key(); }
      QString text() const { return event.text(); }
      int modifiers() const { return event.modifiers(); }
      bool isAutoRepeat() const { return event.isAutoRepeat(); }
      int count() const { return event.count(); }
      quint32 nativeScanCode() const { return event.nativeScanCode(); }
      bool isAccepted() { return event.isAccepted(); }
      void setAccepted(bool accepted) { event.setAccepted(accepted); }
      Q_INVOKABLE bool matches(QKeySequence::StandardKey key) const { return event.matches(key); }
  private:
      QKeyEvent event;
  };
  class MouseToolEvent : public QObject
  {
      Q_OBJECT
      Q_PROPERTY(qreal x READ x)
      Q_PROPERTY(qreal y READ y)
      Q_PROPERTY(int button READ button)
      Q_PROPERTY(int buttons READ buttons)
      Q_PROPERTY(int modifiers READ modifiers)
      Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)
  public:
      MouseToolEvent() : event(QEvent::None, QPointF(), Qt::NoButton, Qt::NoButton, Qt::NoModifier)
      {}
      ~MouseToolEvent() {}
      void reset(const QMouseEvent& me)
      {
        event = me;
      }
      qreal x() const { return event.x(); }
      qreal y() const { return event.y(); }
      int button() const { return event.button(); }
      int buttons() const { return event.buttons(); }
      int modifiers() const { return event.modifiers(); }
      bool isAccepted() { return event.isAccepted(); }
      void setAccepted(bool accepted) { event.setAccepted(accepted); }
  private:
      QMouseEvent event;
  };
  class WheelToolEvent : public QObject
  {
      Q_OBJECT
      Q_PROPERTY(qreal x READ x)
      Q_PROPERTY(qreal y READ y)
      Q_PROPERTY(QPoint angleDelta READ angleDelta)
      Q_PROPERTY(QPoint pixelDelta READ pixelDelta)
      Q_PROPERTY(int buttons READ buttons)
      Q_PROPERTY(int modifiers READ modifiers)
      Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)
  public:
      WheelToolEvent() : event(QPointF(), 0, Qt::NoButton, Qt::NoModifier)
      {}
      void reset(const QWheelEvent& we)
      {
        event = we;
      }
      qreal x() const { return event.x(); }
      qreal y() const { return event.y(); }
      QPoint angleDelta() const { return event.angleDelta(); }
      QPoint pixelDelta() const { return event.pixelDelta(); }
      int buttons() const { return event.buttons(); }
      int modifiers() const { return event.modifiers(); }
      bool isAccepted() { return event.isAccepted(); }
      void setAccepted(bool accepted) { event.setAccepted(accepted); }
  private:
    QWheelEvent event;
  };
}

#endif
