#ifndef _CARTOGRAPHERML_TOOL_H_
#define _CARTOGRAPHERML_TOOL_H_

#include "AbstractTool.h"

namespace CartographerML
{
  class ToolController;
  class Tool : public AbstractTool
  {
    friend class ToolController;
    Q_OBJECT
  public:
    Tool(QObject* _parent = 0);
    ~Tool();
  protected:
    virtual void mouseDoubleClickEvent(MouseToolEvent* event);
    virtual void mouseMoveEvent(MouseToolEvent* event);
    virtual void mousePressEvent(MouseToolEvent* event);
    virtual void mouseReleaseEvent(MouseToolEvent* event);
  signals:
    void doubleClicked(CartographerML::MouseToolEvent* event);
    void pressed(CartographerML::MouseToolEvent* event);
    void moved(CartographerML::MouseToolEvent* event);
    void released(CartographerML::MouseToolEvent* event);
  };
}

#endif
