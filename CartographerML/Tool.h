#ifndef _CARTOGRAPHERML_TOOL_H_
#define _CARTOGRAPHERML_TOOL_H_

#include "AbstractTool.h"

namespace CartographerML
{
  class ToolController;
  class Tool : public AbstractTool
  {
    Q_OBJECT
  public:
    Tool(QObject* _parent = 0);
    ~Tool();
  protected:
    virtual void mouseDoubleClickEvent(MouseToolEvent* event);
    virtual void mouseMoveEvent(MouseToolEvent* event);
    virtual void mousePressEvent(MouseToolEvent* event);
    virtual void mouseReleaseEvent(MouseToolEvent* event);
    virtual void wheelEvent(WheelToolEvent* event);
  signals:
    void doubleClicked(CartographerML::MouseToolEvent* mouse);
    void pressed(CartographerML::MouseToolEvent* mouse);
    void positionChanged(CartographerML::MouseToolEvent* mouse);
    void released(CartographerML::MouseToolEvent* mouse);
    void wheel(CartographerML::WheelToolEvent* wheel);
  };
}

#endif
