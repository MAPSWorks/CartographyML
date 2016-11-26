#ifndef _CARTOGRAPHERML_TOOLCONTROLLER_H_
#define _CARTOGRAPHERML_TOOLCONTROLLER_H_

#include <QQuickItem>

namespace CartographerML
{
  class AbstractTool;
  class AbstractFeaturesSource;
  class ToolController : public QQuickItem
  {
    Q_OBJECT
    Q_PROPERTY(CartographerML::AbstractTool* tool READ tool WRITE setTool NOTIFY toolChanged)
    Q_PROPERTY(CartographerML::AbstractFeaturesSource* currentFeaturesSource READ currentFeaturesSource WRITE setCurrentFeaturesSource NOTIFY currentFeaturesSourceChanged)
  public:
    ToolController(QQuickItem* parent = 0);
    virtual ~ToolController();
    AbstractTool* tool() const;
    void setTool(AbstractTool* _tool);
    CartographerML::AbstractFeaturesSource* currentFeaturesSource() const;
    void setCurrentFeaturesSource(CartographerML::AbstractFeaturesSource* _source);
  signals:
    void toolChanged();
    void currentFeaturesSourceChanged();
  protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void hoverEnterEvent(QHoverEvent* event);
    virtual void hoverMoveEvent(QHoverEvent* event);
    virtual void hoverLeaveEvent(QHoverEvent* event);
  private slots:
    void toolHoverEnabledHasChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
