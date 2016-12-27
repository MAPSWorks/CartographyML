#ifndef _CARTOGRAPHERML_TOOLPROXY_H_
#define _CARTOGRAPHERML_TOOLPROXY_H_

#include "AbstractTool.h"

namespace CartographerML
{
  class ProxyTool : public AbstractTool
  {
    Q_OBJECT
    Q_PROPERTY(CartographerML::AbstractTool* tool READ tool WRITE setTool NOTIFY toolChanged)
  public:
    ProxyTool(QObject* _parent = 0);
    ~ProxyTool();
  public:
    AbstractTool* tool() const;
    void setTool(AbstractTool* _tool);
  protected:
    virtual void toolActivated();
    virtual void toolDeactivated();
    virtual void mouseDoubleClickEvent(MouseToolEvent* event);
    virtual void mouseMoveEvent(MouseToolEvent* event);
    virtual void mousePressEvent(MouseToolEvent* event);
    virtual void mouseReleaseEvent(MouseToolEvent* event);
    virtual void wheelEvent(WheelToolEvent* event);    
  signals:
    void activated();
    void deactivated();
    void toolChanged();
  private slots:
    void updateHoverEnabled();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
