#ifndef _CARTOGRAPHERML_TOOLCONTROLLER_H_
#define _CARTOGRAPHERML_TOOLCONTROLLER_H_

#include <QQuickItem>

namespace CartographerML
{
  class AbstractTool;
  class ToolController : public QQuickItem
  {
    Q_OBJECT
    Q_PROPERTY(CartographerML::AbstractTool* tool READ tool WRITE setTool NOTIFY toolChanged)
  public:
    ToolController(QQuickItem* parent = 0);
    virtual ~ToolController();
    AbstractTool* tool() const;
    void setTool(AbstractTool* _tool);
  signals:
    void toolChanged();
  protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
  private:
    struct Private;
    Private* const d;
  };
}

#endif
