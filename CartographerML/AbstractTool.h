#ifndef _CARTOGRAPHERML_ABSTRACTOOL_H_
#define _CARTOGRAPHERML_ABSTRACTOOL_H_

#include <QObject>


namespace CartographerML
{
  class AbstractFeaturesSource;
  class MouseToolEvent;
  class ToolController;
  class WheelToolEvent;
  class AbstractTool : public QObject
  {
    friend class ToolController;
    Q_OBJECT
    Q_PROPERTY(bool hoverEnabled READ isHoverEnabled WRITE setHoveredEnabled NOTIFY hoverEnabledChanged)
    Q_PROPERTY(CartographerML::AbstractFeaturesSource* featuresSource READ featuresSource WRITE setFeaturesSource NOTIFY featuresSourceChanged)
  public:
    AbstractTool(QObject* _parent = 0);
    ~AbstractTool();
    bool isHoverEnabled() const;
    void setHoveredEnabled(bool _v);
    CartographerML::AbstractFeaturesSource* featuresSource() const;
    void setFeaturesSource(CartographerML::AbstractFeaturesSource* _source);
  signals:
    void hoverEnabledChanged();
    void featuresSourceChanged();
  protected:
    virtual void toolActivated();
    virtual void toolDeactivated();
    virtual void mouseDoubleClickEvent(MouseToolEvent* event);
    virtual void mouseMoveEvent(MouseToolEvent* event);
    virtual void mousePressEvent(MouseToolEvent* event);
    virtual void mouseReleaseEvent(MouseToolEvent* event);
    virtual void wheelEvent(WheelToolEvent* event);
  private:
    struct Private;
    Private* const d;
  };
}

#endif
