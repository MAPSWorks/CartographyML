#ifndef _CARTOGRAPHERML_ABSTRACTOOL_H_
#define _CARTOGRAPHERML_ABSTRACTOOL_H_

#include <QObject>


namespace CartographerML
{
  class MouseToolEvent;
  class ToolController;
  class AbstractTool : public QObject
  {
    friend class ToolController;
    Q_OBJECT
  public:
    AbstractTool(QObject* _parent = 0);
    ~AbstractTool();
  protected:
    virtual void mouseDoubleClickEvent(MouseToolEvent* event);
    virtual void mouseMoveEvent(MouseToolEvent* event);
    virtual void mousePressEvent(MouseToolEvent* event);
    virtual void mouseReleaseEvent(MouseToolEvent* event);
  };
}

#endif
